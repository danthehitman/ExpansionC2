#include "simple2drenderer.h"

namespace ec2 {
    namespace graphics {

        void Simple2DRenderer::submit(const Renderable2D * renderable)
        {
            _renderQueue.push_back((StaticSprite*)renderable);
        }

        void Simple2DRenderer::flush()
        {
            while (!_renderQueue.empty())
            {
                const StaticSprite * sprite = _renderQueue.front();
                sprite->getVao()->bind();
                sprite->getIbo()->bind();

                sprite->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(sprite->getPosition()));
                glDrawElements(GL_TRIANGLES, sprite->getIbo()->getCount(), GL_UNSIGNED_SHORT, nullptr);

                sprite->getVao()->unbind();
                sprite->getIbo()->unbind();

                _renderQueue.pop_front();
            }
        }

    }
}
