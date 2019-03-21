#pragma once

#include <GL/glew.h>

namespace ec2 {
    namespace graphics {
        class IndexBuffer
        {
        private:
            GLuint _bufferId;
            GLuint _count;

        public:
            IndexBuffer(GLushort * data, GLsizei count);
            IndexBuffer(GLuint * data, GLsizei count);
            ~IndexBuffer();

            void bind() const;
            void unbind() const;

            inline GLuint getCount() const { return _count; }
        };
    }
}
