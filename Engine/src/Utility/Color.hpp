#pragma one
#ifndef COLOR_HPP
#define COLOR_HPP

#include <Math/glmath.hpp>

namespace Color
{
    inline Math::vec4 lightgray  = (Math::vec4){200, 200, 200, 255};
    inline Math::vec4 gray       = (Math::vec4){130, 130, 130, 255};
    inline Math::vec4 darkgray   = (Math::vec4){80,  80,  80,  255};
    inline Math::vec4 yellow     = (Math::vec4){253, 249, 0,   255};
    inline Math::vec4 gold       = (Math::vec4){255, 203, 0,   255};
    inline Math::vec4 orange     = (Math::vec4){255, 161, 0,   255};
    inline Math::vec4 pink       = (Math::vec4){255, 109, 194, 255};
    inline Math::vec4 red        = (Math::vec4){230, 41,  55,  255};
    inline Math::vec4 maroon     = (Math::vec4){190, 33,  55,  255};
    inline Math::vec4 green      = (Math::vec4){0,   228, 48,  255};
    inline Math::vec4 lime       = (Math::vec4){0,   158, 47,  255};
    inline Math::vec4 darkgreen  = (Math::vec4){0,   117, 44,  255};
    inline Math::vec4 skyblue    = (Math::vec4){102, 191, 255, 255};
    inline Math::vec4 blue       = (Math::vec4){0,   121, 241, 255};
    inline Math::vec4 darkblue   = (Math::vec4){0,   82,  172, 255};
    inline Math::vec4 purple     = (Math::vec4){200, 122, 255, 255};
    inline Math::vec4 violet     = (Math::vec4){135, 60,  190, 255};
    inline Math::vec4 darkpurple = (Math::vec4){112, 31,  126, 255};
    inline Math::vec4 beige      = (Math::vec4){211, 176, 131, 255};
    inline Math::vec4 brown      = (Math::vec4){127, 106, 79,  255};
    inline Math::vec4 darkbrown  = (Math::vec4){76,  63,  47,  255};
    inline Math::vec4 white      = (Math::vec4){255, 255, 255, 255};
    inline Math::vec4 black      = (Math::vec4){0,   0,   0,   255};
    inline Math::vec4 magenta    = (Math::vec4){255, 0,   255, 255};

    inline static Math::vec4 HexToColor(unsigned int hexValue)
    {
        Math::vec4 rgbColor;
        
        if (hexValue >= (unsigned int)0x01000000)
        {
            rgbColor.x = ((hexValue >> 24) & 0xFF); // Extract the RR byte
            rgbColor.y = ((hexValue >> 16) & 0xFF); // Extract the GG byte
            rgbColor.z = ((hexValue >> 8) & 0xFF);  // Extract the BB byte
            rgbColor.w = ((hexValue)&0xFF);         // Extract the AA byte
        }
        else
        {
            rgbColor.x = ((hexValue >> 16) & 0xFF); // Extract the RR byte
            rgbColor.y = ((hexValue >> 8) & 0xFF);  // Extract the GG byte
            rgbColor.z = ((hexValue)&0xFF);         // Extract the BB byte
            rgbColor.w = 255;
        }

        return rgbColor;
    }
}
#endif