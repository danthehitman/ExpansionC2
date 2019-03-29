#pragma once

#include "renderable2D.h"

namespace ec2 {
    namespace graphics {
        class Label : public Renderable2D
        {
        private:
            std::string _text;
        public:
            Label(std::string text, float x, float y, maths::vec4 color);
            ~Label();

            void submit(Renderer2D * renderer) const override; 
        };
    }
}

