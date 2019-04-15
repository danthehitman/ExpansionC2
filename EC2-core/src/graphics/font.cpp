#include "font.h"

namespace ec2
{
    Font::Font(std::string name, std::string filename, int size)
        : _name(name), _filename(filename), _size(size)
    {
        _ftAtlas = ftgl::texture_atlas_new(512, 512, 2);
        _ftFont = ftgl::texture_font_new_from_file(_ftAtlas, size, filename.c_str());
    }
}
