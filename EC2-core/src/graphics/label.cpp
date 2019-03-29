#include "label.h"

namespace ec2 {
    namespace graphics {

        Label::Label(std::string text, float x, float y, maths::vec4 color)
            : Renderable2D(), _text(text)
        {
            _position = maths::vec3(x, y, 0.0f);
            _color = color;
        }


        Label::~Label()
        {
        }
        void Label::submit(Renderer2D * renderer) const
        {
            renderer->drawString(_text, _position, _color);
        }
    }
}
