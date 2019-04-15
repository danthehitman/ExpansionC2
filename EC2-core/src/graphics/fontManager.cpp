#include "fontManager.h"

namespace ec2
{

    std::vector<Font*> FontManager::_fonts;

    void FontManager::add(Font* font)
    {
        _fonts.push_back(font);
    }

    Font* FontManager::get(const std::string& name)
    {
        for(Font * font : _fonts)
        {
            if (font->getName() == name)
            {
                return font;
            }
        }

        //TODO: Maybe return default font.
        return nullptr;
    }

    Font* FontManager::get(const std::string& name, unsigned int size)
    {
        for (Font* font : _fonts)
        {
            if (font->getSize() == size && font->getName() == name)
            {
                return font;
            }
        }

        //TODO: Maybe return default font.
        return nullptr;
    }
    
    void FontManager::clean()
    {
        for (int i = 0; i < _fonts.size(); i++)
        {
            delete _fonts[i];
        }
    }
}
