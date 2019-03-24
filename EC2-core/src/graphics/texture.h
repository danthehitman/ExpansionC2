#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage.h>
#include "../utils/ImageLoad.h"

namespace ec2 {
    namespace graphics {
        class Texture
        {
            std::string _filename;
            GLuint _tid;
            GLsizei _width, _height;
        public:
            Texture(const std::string & filename);
            ~Texture();
            void bind() const;
            void unbind() const;

            inline const unsigned int getWidth() const {return _width;}
            inline const unsigned int getHeight() const { return _height; }

        private:
            GLuint load();
        };
    }
}

