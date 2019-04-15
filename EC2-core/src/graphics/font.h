#pragma once

#include <string>
#include "../../ext/freetype-gl/freetype-gl.h"

namespace ec2
{
    class Font
    {
    private:
        ftgl::texture_atlas_t* _ftAtlas;
        ftgl::texture_font_t* _ftFont;
        unsigned int _size;
        std::string _filename;
        std::string _name;
    public:
        Font(std::string name, std::string filename, int size);

        inline ftgl::texture_font_t* getFtFont() const { return _ftFont; }

        inline const unsigned int getId() const { return _ftAtlas->id; }
        inline const std::string & getName() const { return _name; }
        inline const std::string& getFilename() const { return _filename; }
        inline const int getSize() const { return _size; }
    };
}

