#include "buffer.h"

namespace ec2 {
    namespace graphics {

        Buffer::Buffer(GLfloat * data, GLsizei count, GLuint componentCount)
            : _componentCount(componentCount)
        {

            glGenBuffers(1, &_bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


        Buffer::~Buffer()
        {
        }

        void graphics::Buffer::bind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
        }

        void graphics::Buffer::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}