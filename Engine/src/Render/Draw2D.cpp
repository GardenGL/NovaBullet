#include "Draw2D.hpp"

#include "Rect.hpp"
#include "Line.hpp"

#include "Font/Font.hpp"
#include "Sprite.hpp"

namespace Draw2D
{
    void initialize()
    {
        EndMode2D();
        LineRender::initialize();
        Rect_render::initialize();

        Sprite_render::initialize();
        InitFont(Window::width, Window::height, "assets/Fonts/DroidSans.ttf");
    }

    Math::mat4x4 l_view;
    Math::mat4x4 l_projection;

    void BeginMode2D(Math::mat4x4 view, Math::mat4x4 projection)
    {
        l_view = view;
        l_projection = projection;
    }
    
    void EndMode2D()
    {
        l_view = Math::mat4x4();
        l_projection = Math::Ortho(0.0f, (float)Window::width, (float)Window::height, 0.0f, 1.0f, -1.0f);
    }

    void Rectangle(float x , float y , float width , float height , Math::vec4 color, float angle)
    {
        Rect_render::DrawRectangle(l_view, l_projection, x, y, width, height, angle, color);
    }

    void Rectangle(Rect r , Math::vec4 color ,float angle )
    {
        Rect_render::DrawRectangle(l_view, l_projection, r.x, r.y, r.width, r.height, angle, color);
    }

    void Sprite(float x, float y, float width, float height, Texture *texture, Math::vec4 color, float angle)
    {
        Sprite_render::DrawSprite(l_view, l_projection, x, y, width, height, angle, texture, color);
    }

    void Sprite(Rect r, Texture *texture, Math::vec4 color , float angle)
    {
        Sprite_render::DrawSprite(l_view, l_projection , r.x, r.y, r.width, r.height, angle, texture, color);
    }

    void Line(Math::vec2 start, Math::vec2 end, Math::vec4 color)
    {
        LineRender::DrawLine(start, end, color);
    }

    void Line(float start_x, float start_y, float end_x, float end_y, Math::vec4 color)
    {
        LineRender::DrawLine(Math::vec2(start_x, start_y), Math::vec2(end_x, end_y), color);
    }

    void Line_Render()
    {
        LineRender::Render(l_view, l_projection);
    }

    namespace Font
    {
        void Text(std::string text, float x, float y, float size, int align, Math::vec4 color)
        {
            DrawTextF(text, x, y, size, align, color);
        }
    }
    void terminate()
    {
        LineRender::terminate();
        Rect_render::terminate();
    }
};
