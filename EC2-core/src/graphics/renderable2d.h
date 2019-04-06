#pragma once

#include"buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"
#include "../math/maths.h"
#include "shader.h"
#include "renderer2d.h"
#include "texture.h"

namespace ec2 {
    namespace graphics {

        struct VertexData
        {
            maths::vec3 vertex;
            maths::vec2 uv; //texture coordinates?  apparently because uv is to texture coords as xy is to normal coords.
            float tid;
            unsigned int color;
        };

        class Renderable2D
        {
        protected:
            maths::vec3 _position;
            maths::vec2 _size;
            unsigned int _color;
            std::vector<maths::vec2> _uvs;
            Texture * _texture;
        protected:
            Renderable2D() 
                : _texture(nullptr)
            {
                setUvDefaults();
            }


        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
                : _position(position), _size(size), _color(color), _texture(nullptr)
            {
                setUvDefaults();
            }

            virtual ~Renderable2D()
            {
                
            }

            virtual void submit(Renderer2D * renderer) const
            {
                renderer->submit(this);
            }

            void setColor(unsigned int color)
            {
                _color = color;
            }
            
            void setColor(const maths::vec4& color) 
            {


                int r = color.x * 255.0f;
                int g = color.y * 255.0f;
                int b = color.z * 255.0f;
                int a = color.w * 255.0f;

                _color = a << 24 | b << 16 | g << 8 | r;
            }

            inline const maths::vec3 & getPosition() const { return _position; }
            inline const maths::vec2 & getSize() const { return _size; }
            inline const unsigned int & getColor() const { return _color; }
            inline const std::vector<maths::vec2> & getUvs() const { return _uvs; }

            inline const GLuint getTid() const 
            { 
                return _texture ? _texture->getId() : 0;
            }
        private:
            void setUvDefaults()
            {
                _uvs.push_back(maths::vec2(0, 0));
                _uvs.push_back(maths::vec2(0, 1));
                _uvs.push_back(maths::vec2(1, 1));
                _uvs.push_back(maths::vec2(1, 0));
            }

        };

    }
}
