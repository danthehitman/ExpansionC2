#pragma once

#include <vector>
#include "font.h"

namespace ec2
{
    class FontManager
    {
    private:
        static std::vector<Font*> _fonts;
    public:
        static void add(Font* font);
        static Font* get(const std::string& name);
        static Font* get(const std::string& name, unsigned int size);
        static void clean();

    private:
        FontManager();
    };
}

