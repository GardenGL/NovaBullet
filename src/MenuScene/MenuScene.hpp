// -----[ MenuScene.h ]----- //
#include <Engine.hpp>

#include "UI.hpp"

class MenuScene : public Scene
{
private:
    UI::Button *button_play;
    UI::Button *button_exit;

public:
    virtual void Start()
    {
        Inputs::SetCursorMode(1);

        float y = 300;
        button_play = new UI::Button((Rect){30, y, 620, 50.0f}, "Играть");
        y += 60;
        button_exit = new UI::Button((Rect){30, y, 620, 50.0f}, "Выйти");
    }

    virtual void Update()
    {
        if (button_play->Update())
        {
            return SceneManager::changeScene("game_scene");
        }

        if (button_exit->Update())
        {
            return Window::Close();
        }
    }

    virtual void Render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Draw2D::Sprite(0, 0, Window::width, Window::height, ResourceManager::GetTexture("BG:Universe"), Color::white);

        static float BGrotation = 0.0f;
        BGrotation = BGrotation * Time::getDelta() * 5.0f;
        Draw2D::Sprite(0.0f, 0.0f, static_cast<float>(Window::width * 2.0f),
                       static_cast<float>(Window::width * 2.0f),

                       ResourceManager::GetTexture("BG:Planets"),
                       Color::white, BGrotation);

        Draw2D::Rectangle((Rect){20.0f, 0.0f, 640.0f, 1080.0f}, (Math::vec4){130, 130, 130, 100});
        Draw2D::Sprite((Rect){280.0f, 0.0f, 120, 120}, ResourceManager::GetTexture("Logo"), Color::white);

        button_play->Render();
        button_exit->Render();
    }

    virtual void Destroy()
    {
        delete button_exit;
        delete button_play;
    }
};
