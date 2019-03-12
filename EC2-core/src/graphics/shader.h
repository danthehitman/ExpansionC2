#pragma once

#include "../math/maths.h"
#include "../utils/fileutils.h"
#include <GL/glew.h>
#include <iostream>
#include<vector>

namespace ec2 {
    namespace graphics {

        class Shader
        {
        private:
            GLuint _shaderId;
            const char * _vertPath;
            const char * _fragPath;
        public:
            Shader(const char* vertexPath, const char* fragPath);
            ~Shader();

            void setUniform1f(const GLchar * name, float value);
            void setUniform1i(const GLchar * name, int value);
            void setUniform2f(const GLchar * name, const maths::vec2 & vector);
            void setUniform3f(const GLchar * name, const maths::vec3 & vector);
            void setUniform4f(const GLchar * name, const maths::vec4 & vector);
            void setUniformMat4(const GLchar * name, const maths::mat4 & matrix);

            void enable() const;
            void disable() const;
        private:
            GLuint load();
            GLint getUniformLocation(const GLchar * name);
        };

    }
}
