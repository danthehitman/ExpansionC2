#include "texture.h"

namespace ec2 {
    namespace graphics {

        Texture::Texture(const std::string & filename)
            :_filename(filename)
        {
            _tid = load();
        }
        
        Texture::~Texture()
        {

        }

        void Texture::bind() const
        {
            glBindTexture(GL_TEXTURE_2D, _tid);
        }

        void Texture::unbind() const
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        GLuint Texture::load()
        {
            BYTE * pixels = load_image(_filename.c_str(), &_width, &_height);

            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            glBindTexture(GL_TEXTURE_2D, 0);

            // delete[] pixels;

            return result;
        }
    }
}
