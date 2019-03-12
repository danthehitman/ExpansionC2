#pragma once

#include"buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"
#include "../math/maths.h"
#include "shader.h"

namespace ec2 {
    namespace graphics {

        class Renderable2D
        {
        protected:
            maths::vec3 _position;
            maths::vec2 _size;
            maths::vec4 _color;

            Shader & _shader;
            VertexArray * _vertexArray;
            IndexBuffer * _indexBuffer;

        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader & shader)
                : _position(position), _size(size), _color(color), _shader(shader)
            {
                _vertexArray = new VertexArray();
                GLfloat vertices[] = 
                {
                    0, 0, 0,
                    0, size.y, 0,
                    size.x, size.y, 0,
                    size.x, 0, 0
                };

                GLfloat colors[] =
                {
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w
                };

                _vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
                _vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

                GLushort indices[] =
                {
                    0, 1, 2, 2, 3, 0
                };

                _indexBuffer = new IndexBuffer(indices, 6);
            }

            ~Renderable2D()
            {
                delete _vertexArray;
                delete _indexBuffer;
            }
            
            inline const VertexArray* getVao() const { return _vertexArray; }
            inline const IndexBuffer* getIbo() const { return _indexBuffer; }

            inline Shader & getShader() const { return _shader; }

            inline const maths::vec3 & getPosition() const { return _position; }
            inline const maths::vec2 & getSize() const { return _size; }
            inline const maths::vec4 & getColor() const { return _color; }

        };

    }
}
