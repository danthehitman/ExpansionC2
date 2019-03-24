#pragma once

#include <deque>
#include "staticsprite.h"
#include "renderer2d.h"
#include "renderable2d.h"

namespace ec2 {
    namespace graphics {
        class Simple2DRenderer : public Renderer2D
        {
        private:
            std::deque<const StaticSprite*> _renderQueue;
        public:
            void submit(const Renderable2D * renderable) override;
            void flush() override;
        };
    }
}
