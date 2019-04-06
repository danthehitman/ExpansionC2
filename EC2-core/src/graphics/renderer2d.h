#pragma once

#include <vector>
#include <GL/glew.h>
#include "../math/maths.h"


namespace ec2 {
    namespace graphics {
        class Renderable2D;

        class Renderer2D
        {
        protected:
            std::vector<maths::mat4> _transformationStack;
            const maths::mat4 * _transformationBack;
        protected:
            Renderer2D()
            {
                _transformationStack.push_back(maths::mat4::identity());
                _transformationBack = &_transformationStack.back();
            }
        public:
            void push(const maths::mat4& matrix, bool override = false)
            {
                if (override)
                {
                    _transformationStack.push_back(matrix);
                }
                else
                {
                    _transformationStack.push_back(_transformationStack.back() * matrix);
                }
                _transformationBack = &_transformationStack.back();
            }

            void pop()
            {
                //TODO: Add to log.
                if (_transformationStack.size() > 1)
                {
                    _transformationStack.pop_back();
                }

                _transformationBack = &_transformationStack.back();
            }

            virtual void begin() {}
            virtual void submit(const Renderable2D * renderable) = 0;
            virtual void drawString(const std::string & text, const maths::vec3 & position, unsigned int color) {}
            virtual void end() {}
            virtual void flush() = 0;
        };
    }
}

