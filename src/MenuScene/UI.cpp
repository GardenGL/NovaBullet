#include "UI.hpp"
#include <Engine.hpp>

namespace UI
{
    bool Collision_RectvsRect(Rect rect1, Rect rect2)
    {
        return (rect1.x < rect2.x + rect2.width &&
                rect1.x + rect1.width > rect2.x &&
                rect1.y < rect2.y + rect2.height &&
                rect1.y + rect1.height > rect2.y);
    }

    Button::Button(Rect rec, std::string t)
    {
        rect = rec;
        title = t;
        collide = false;
    }

    bool Button::Update()
    {
        Rect cursor;
        cursor.x = Inputs::x ;
        cursor.y = Inputs::y ;
        cursor.width = 10 ;
        cursor.height = 10 ;

        collide = Collision_RectvsRect(cursor, rect);

        if (collide == true)
        {

            if (Inputs::IsKeyPressed(Inputs::MOUSE_BUTTON_LEFT))
            {
                buttonstate = 2;
            }
            else
            {
                buttonstate = 1;
            }
            if (Inputs::IsKeyReleased(Inputs::MOUSE_BUTTON_LEFT))
            {
                return true;
            }
        }
        else
        {
            buttonstate = 3;
        }
        return false;
    }

    void Button::Render()
    {
        switch (buttonstate)
        {
        case 1:
            Draw2D::Rectangle(rect, Color::red);
            break;
        case 2:
            Draw2D::Rectangle(rect, Color::purple);
            break;
        case 3:
            Draw2D::Rectangle(rect, Color::gray);
            break;

        default:
            break;
        }
        Draw2D::Font::Text(title.c_str(), rect.x + rect.width / 2.0f + 20, rect.y + rect.height / 1.5f, 40, Draw2D::Font::ALIGN_CENTER, Color::white);
    }
}