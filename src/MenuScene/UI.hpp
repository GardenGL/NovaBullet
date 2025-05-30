#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <Engine.hpp>

namespace UI
{
    class Button
    {
     public:
        Rect rect;
        std::string title;
        bool collide;
        int buttonstate;

        Button(Rect rec, std::string t);
        
        bool Update();
        void Render(); 
    };

}

#endif