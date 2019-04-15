#include "label.h"

namespace ec2 {
    namespace graphics {

        Label::Label(std::string text, float x, float y,unsigned int color)
            : Renderable2D(), text(text), position(_position), _font(FontManager::get("SourceSansPro"))
        {
            _position = maths::vec3(x, y, 0.0f);
            _color = color;
        }

        Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
            : Renderable2D(), text(text), position(_position), _font(font)
        {
            _position = maths::vec3(x, y, 0.0f);
            _color = color;
        }

        Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
            : Renderable2D(), text(text), position(_position), _font(FontManager::get(font))
        {
            _position = maths::vec3(x, y, 0.0f);
            _color = color;

            validateFont(font);
        }

        Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
            : Renderable2D(), text(text), position(_position), _font(FontManager::get(font, size))
        {
            _position = maths::vec3(x, y, 0.0f);
            _color = color;

            validateFont(font, size);
        }

        Label::~Label()
        {
        }
        void Label::submit(Renderer2D * renderer) const
        {
            renderer->drawString(text, position, *_font, _color);
        }

        void Label::validateFont(const std::string& name, int size)
        {
            if (_font != nullptr)
                return;

            std::cout << "NULL FONT! Font= " << name;
            if (size > 0)
            {
                std::cout << ", Size=" << size;
            }
            std::cout << std::endl;

            _font = FontManager::get("SourceSansPro");
        }
    }
}
