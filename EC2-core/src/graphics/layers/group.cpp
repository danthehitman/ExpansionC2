#include "group.h"

namespace ec2 {
    namespace graphics {
        Group::Group(const maths::mat4& transform)
            : _transformationMatrix(transform)
        {
        }

        Group::~Group()
        {
            for (int i = 0; i < _renderables.size(); i++)
            {
                delete _renderables[i];
            }
        }

        void Group::add(Renderable2D * renderable)
        {
            _renderables.push_back(renderable);
        }

        void Group::submit(Renderer2D * renderer) const
        {
            for (const Renderable2D* renderable : _renderables)
            {
                renderer->push(_transformationMatrix);
                renderable->submit(renderer);
                renderer->pop();
            }
        }
    }
}
