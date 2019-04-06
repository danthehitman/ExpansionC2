#include "batchrenderer2d.h"

namespace ec2 {
    namespace graphics {

        BatchRenderer2D::BatchRenderer2D()
        {
            init();
        }

        BatchRenderer2D::~BatchRenderer2D()
        {
            delete _ibo;
            glDeleteBuffers(1, &_vbo);
        }

        void BatchRenderer2D::init()
        {
            glGenVertexArrays(1, &_vao);
            glGenBuffers(1, &_vbo);

            glBindVertexArray(_vao);
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_UV_INDEX);
            glEnableVertexAttribArray(SHADER_TID_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);

            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

            glBindBuffer(GL_ARRAY_BUFFER, 0);
                        
            GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
            
            int offset = 0;
            for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6)
            {

                indices[  i  ] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }

            _ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

            glBindVertexArray(0);

            _ftAtlas = ftgl::texture_atlas_new(512, 512, 2);
            _ftFont = ftgl::texture_font_new_from_file(_ftAtlas, 32, "SourceCodePro-Light.ttf");

            //ftgl::texture_glyph_t *glyph =  ftgl::texture_font_get_glyph(_ftFont, 'A');


        }

        void BatchRenderer2D::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            _buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BatchRenderer2D::submit(const Renderable2D * renderable)
        {
            const maths::vec3 & position = renderable->getPosition();
            const maths::vec2 & size = renderable->getSize();
            const unsigned int color = renderable->getColor();
            const std::vector<maths::vec2> & uvs = renderable->getUvs();
            const GLuint tid = renderable->getTid();

            float ts = 0.0f;
            if (tid > 0)
            {
                bool found = false;
                for (int i = 0; i < _textureSlots.size(); i++)
                {
                    if (_textureSlots[i] == tid)
                    {
                        ts = (float)(i + 1);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    if (_textureSlots.size() >= 32)
                    {
                        end();
                        flush();
                        begin();
                    }
                    _textureSlots.push_back(tid);
                    ts = (float)_textureSlots.size();
                }
            }

            _buffer->vertex = *_transformationBack * position;
            _buffer->uv = uvs[0];
            _buffer->tid = ts;
            _buffer->color = color;
            _buffer++;

            _buffer->vertex = *_transformationBack * maths::vec3(position.x, position.y + size.y, position.z);
            _buffer->uv = uvs[1];
            _buffer->tid = ts;
            _buffer->color = color;
            _buffer++;

            _buffer->vertex = *_transformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
            _buffer->uv = uvs[2];
            _buffer->tid = ts;
            _buffer->color = color;
            _buffer++;

            _buffer->vertex = *_transformationBack * maths::vec3(position.x + size.x, position.y, position.z);
            _buffer->uv = uvs[3];
            _buffer->tid = ts;
            _buffer->color = color;
            _buffer++;

            _indexCount += 6;
        }

        void BatchRenderer2D::drawString(const std::string & text, const maths::vec3 & position, unsigned int color)
        {
            using namespace ftgl;

            float ts = 0.0f;

            bool found = false;
            for (int i = 0; i < _textureSlots.size(); i++)
            {
                if (_textureSlots[i] == _ftAtlas->id)
                {
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                if (_textureSlots.size() >= 32)
                {
                    end();
                    flush();
                    begin();
                }
                _textureSlots.push_back(_ftAtlas->id);
                ts = (float)_textureSlots.size();
            }

            float scaleX = 960.0f / 32.0f;
            float scaleY = 540.0f / 18.0f;

            float x = position.x;

            for (int i = 0; i < text.length(); ++i)
            {
                texture_glyph_t *glyph = texture_font_get_glyph(_ftFont, text[i]);

                if (glyph != NULL)
                {
                    if (i > 0)
                    {
                        float kerning = texture_glyph_get_kerning(glyph, text[i-1]);
                        x += kerning / scaleX;
                    }

                    float x0 = x + glyph->offset_x / scaleX;
                    float y0 = position.y + glyph->offset_y / scaleY;
                    float x1 = x0 + glyph->width / scaleX;
                    float y1 = y0 - glyph->height / scaleY;

                    float u0 = glyph->s0;
                    float v0 = glyph->t0;
                    float u1 = glyph->s1;
                    float v1 = glyph->t1;

                    _buffer->vertex = *_transformationBack * maths::vec3(x0, y0, 0);
                    _buffer->uv = maths::vec2(u0, v0);
                    _buffer->tid = ts;
                    _buffer->color = color;
                    _buffer++;

                    _buffer->vertex = *_transformationBack * maths::vec3(x0, y1, 0);
                    _buffer->uv = maths::vec2(u0, v1);
                    _buffer->tid = ts;
                    _buffer->color = color;
                    _buffer++;

                    _buffer->vertex = *_transformationBack *maths::vec3(x1, y1, 0);
                    _buffer->uv = maths::vec2(u1, v1);
                    _buffer->tid = ts;
                    _buffer->color = color;
                    _buffer++;

                    _buffer->vertex = *_transformationBack *maths::vec3(x1, y0, 0);
                    _buffer->uv = maths::vec2(u1, v0);
                    _buffer->tid = ts;
                    _buffer->color = color;
                    _buffer++;

                    _indexCount += 6;

                    x += glyph->advance_x / scaleX;
                }
            }
        }

        void BatchRenderer2D::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void BatchRenderer2D::flush()
        {
            for (int i = 0; i < _textureSlots.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, _textureSlots[i]);
            }

            glBindVertexArray(_vao);
            _ibo->bind();

            glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, NULL);

            _ibo->unbind();
            glBindVertexArray(0);

            _indexCount = 0;
        }
    }
}