#include "sprite.h"

namespace ec2 {
    namespace graphics {

        Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
            : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color)
        {

        }

        Sprite::Sprite(float x, float y, float width, float height, Texture * texture)
            : Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff)
        {
            _texture = texture;
        }
    }
}
