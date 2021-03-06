#include "indexbuffer.h"

namespace ec2 {
    namespace graphics {

        IndexBuffer::IndexBuffer(GLushort * data, GLsizei count)
            : _count(count)
        {
            glGenBuffers(1, &_bufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::IndexBuffer(GLuint * data, GLsizei count)
            : _count(count)
        {
            glGenBuffers(1, &_bufferId);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::~IndexBuffer()
        {
            glDeleteBuffers(1, &_bufferId);
        }

        void graphics::IndexBuffer::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
        }

        void graphics::IndexBuffer::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}
