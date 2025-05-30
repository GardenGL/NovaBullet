#include "Engine.hpp"

    namespace Engine
    {
        void Initialize(int width, int height, const char* title)
        {
            Window::initialize(width, height, title);
            Inputs::initialize();
            Draw2D::initialize();

        }

        void terminate()
        {
            Window::terminate();
            Inputs::terminate();
            Draw2D::terminate();
        }
    }