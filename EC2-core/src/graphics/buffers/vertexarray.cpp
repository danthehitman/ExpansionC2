#include "vertexarray.h"


namespace ec2 {
    namespace graphics {
        VertexArray::VertexArray()
        {
            glGenVertexArrays(1, &_arrayId);
        }

        VertexArray::~VertexArray()
        {
            for (int i = 0; i < _buffers.size(); i++)
            {
                delete _buffers[i];
            }
        }

        void VertexArray::addBuffer(Buffer * buffer, GLuint index)
        {
            bind();
            buffer->bind();

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();
        }

        void VertexArray::bind() const
        {
            glBindVertexArray(_arrayId);
        }

        void VertexArray::unbind() const
        {
            glBindVertexArray(0);
        }
    }
}
