#ifndef DRAW2D_HPP
#define DRAW2D_HPP
#include <Math/glmath.hpp>
#include <string>
#include <Utility/Color.hpp>
class Texture;

typedef struct
{
    float x, y, width, height;
} Rect;

namespace Draw2D
{
    void initialize();

    void BeginMode2D(Math::mat4x4 view, Math::mat4x4 projection);
    void EndMode2D(); 

    void Rectangle(float x , float y, float width , float height ,   Math::vec4 color, float angle = 0.0f);
    void Rectangle(Rect r, Math::vec4 color, float angle = 0.0f);

    void Sprite(float x, float y, float width, float height,  Texture *texture, Math::vec4 color, float angle = 0.0f);
    void Sprite(Rect r, Texture *texture, Math::vec4 color, float angle = 0.0f);

    void Line(Math::vec2 start, Math::vec2 end, Math::vec4 color);
    void Line(float sx, float sy, float ex, float ey, Math::vec4 color);
    void Line_Render();

    void terminate();

    namespace Font
    {
        enum Alignment
        {
            ALIGN_LEFT = 1,
            ALIGN_CENTER = 2,
            ALIGN_RIGHT = 4,
            ALIGN_TOP = 8,
            ALIGN_MIDDLE = 16,
            ALIGN_BOTTOM = 32
        };

        void Text(std::string text, float x, float y, float size, int align, Math::vec4 color);
    }
};
#endif