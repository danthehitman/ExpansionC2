#pragma once

#include"buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"
#include "../math/maths.h"
#include "shader.h"

namespace ec2 {
    namespace graphics {

        struct VertexData
        {
            maths::vec3 vertex;
            //maths::vec4 color;
            unsigned int color;
        };

        class Renderable2D
        {
        protected:
            maths::vec3 _position;
            maths::vec2 _size;
            maths::vec4 _color;


        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
                : _position(position), _size(size), _color(color)
            {
                
            }

            virtual ~Renderable2D()
            {
                
            }

            inline const maths::vec3 & getPosition() const { return _position; }
            inline const maths::vec2 & getSize() const { return _size; }
            inline const maths::vec4 & getColor() const { return _color; }

        };

    }
}
