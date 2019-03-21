#pragma once

#include "renderable2d.h"

namespace ec2 {
    namespace graphics {

        class StaticSprite : public Renderable2D
        {
        private:
            Shader & _shader;
            VertexArray * _vertexArray;
            IndexBuffer * _indexBuffer;
        public:
            StaticSprite(float x, float y, float width, float height, const maths::vec4 & color, Shader & shader);
            ~StaticSprite();

            inline const VertexArray* getVao() const { return _vertexArray; }
            inline const IndexBuffer* getIbo() const { return _indexBuffer; }

            inline Shader & getShader() const { return _shader; }
        };
    }
}

