#include "simple2drenderer.h"

namespace ec2 {
    namespace graphics {

        void Simple2DRenderer::submit(const Renderable2D * renderable)
        {
            _renderQueue.push_back(renderable);
        }

        void Simple2DRenderer::flush()
        {
            while (!_renderQueue.empty())
            {
                const Renderable2D * renderable = _renderQueue.front();
                renderable->getVao()->bind();
                renderable->getIbo()->bind();

                renderable->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(renderable->getPosition()));
                glDrawElements(GL_TRIANGLES, renderable->getIbo()->getCount(), GL_UNSIGNED_SHORT, nullptr);

                renderable->getVao()->unbind();
                renderable->getIbo()->unbind();

                _renderQueue.pop_front();
            }
        }

    }
}
