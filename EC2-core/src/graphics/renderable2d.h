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
            maths::vec4 _color;
            std::vector<maths::vec2> _uvs;
            Texture * _texture;
        protected:
            Renderable2D() 
                : _texture(nullptr)
            {
                setUvDefaults();
            }


        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
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

            inline const maths::vec3 & getPosition() const { return _position; }
            inline const maths::vec2 & getSize() const { return _size; }
            inline const maths::vec4 & getColor() const { return _color; }
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
