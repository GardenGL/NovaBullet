#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <Math/glmath.hpp>

enum Alignment
{
    ALIGN_LEFT = 1,
    ALIGN_CENTER = 2,
    ALIGN_RIGHT = 4,
    ALIGN_TOP = 8,
    ALIGN_MIDDLE = 16,
    ALIGN_BOTTOM = 32
};

void InitFont(int width, int height, const char *path);
void DrawTextF(std::string text, float x, float y, float size, int align, Math::vec4 color);

#endif