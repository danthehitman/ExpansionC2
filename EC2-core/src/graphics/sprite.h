#pragma once

#include "renderable2d.h"

namespace ec2 {
    namespace graphics {
        class Sprite : public Renderable2D
        {
        public:
            Sprite(float x, float y, float width, float height, const maths::vec4 & color);
        };
    }
}

