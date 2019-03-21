#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace ec2 {
    namespace graphics {

        class Layer
        {
        protected:
            Renderer2D* _renderer;
            std::vector<Renderable2D*> _renderables;
            Shader* _shader;
            maths::mat4 _projectionMatrix;
        protected:
            Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
        public:
            virtual ~Layer();
            virtual void add(Renderable2D* renderable);
            virtual void render();
        };

    }
}