#pragma once

#include "renderable2d.h"
#include <GL/glew.h>
#include "../math/maths.h"

namespace ec2 {
    namespace graphics {
        class Renderer2D
        {
        public:
            virtual void submit(const Renderable2D * renderable) = 0;
            virtual void flush() = 0;
        };
    }
}

