#pragma once

#include "renderable2D.h"
#include "fontManager.h"

namespace ec2 {
    namespace graphics {
        class Label : public Renderable2D
        {
        public:
            Font* _font;
            std::string text;
            maths::vec3 & position;
            float x, y;
        public:
            Label(std::string text, float x, float y, unsigned int color);
            Label(std::string text, float x, float y, Font* font, unsigned int color);
            Label(std::string text, float x, float y, const std::string& font, unsigned int color);
            Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
            ~Label();

            void submit(Renderer2D * renderer) const override; 

        private:
            void validateFont(const std::string& name, int size = -1);
        };
    }
}

