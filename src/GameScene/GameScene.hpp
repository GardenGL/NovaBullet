#include <Engine.hpp>

#include <vector>
#include <algorithm>
#include <cmath>

#include "Entity/Player.hpp"
#include "Entity/Mob.hpp"
#include "Entity/Meteor.hpp"

#include "World/Constants.hpp"

#include "World/Utils.hpp"

#include "Camera2D.hpp"

class GameScene : public Scene
{
private:
    GameObject *gameWorld;

    void SpawnRandomMob()
    {
        Mob *mobPtr = new Mob(Random::Float(0.0f, GameConstants::WORLD_WIDTH), Random::Float(0.0f, GameConstants::WORLD_HEIGHT));
        gameWorld->add_child(mobPtr);
    }

    void SpawnRandomMeteor()
    {
        Meteor *meteor = new Meteor(Random::Float(0.0f, GameConstants::WORLD_WIDTH), Random::Float(0.0f, GameConstants::WORLD_HEIGHT / 2));
        gameWorld->add_child(meteor);
    }

public:
    GameScene() : gameWorld(nullptr) {}

    virtual ~GameScene()
    {
        if (gameWorld)
            delete gameWorld;
    }

    virtual void Start()
    {
        Inputs::SetCursorMode(0);
        bulletManager.ClearHitBoxes();

        // Создаем игровой мир как GameObject
        gameWorld = new GameObject("GameWorld");

        // Спавним мобов
        for (int i = 0; i < 40; i++)
        {
            SpawnRandomMob();
        }

        // Спавним метеориты
        for (int i = 0; i < 200; i++)
        {
            SpawnRandomMeteor();
        }
        // Создаем и добавляем игрока
        Player *playerPtr = new Player(GameConstants::CELL_SIZE * 2, GameConstants::CELL_SIZE * 2, GameConstants::CELL_SIZE * 2, GameConstants::CELL_SIZE * 2, 2);
        state.player = playerPtr;
        gameWorld->add_child(playerPtr);
    }

    virtual void Update()
    {
        if (Inputs::IsKeyDown(Inputs::KEY_ESCAPE))
        {
            return SceneManager::changeScene("main_menu");
        }

        bulletManager.Update(Time::getDelta());

        if (Inputs::IsKeyPressed(Inputs::KEY_TAB))
        {
            Inputs::toggleCursor();
        }

        // Обновляем всю иерархию объектов
        if (gameWorld)
        {
            // В методе Update GameScene
            gameWorld->remove_if([](GameObject *obj)
            {
                if (auto mob = dynamic_cast<Mob*>(obj)) 
                {
                    return !mob->isAlive();
                }
                if (auto meteor = dynamic_cast<Meteor*>(obj))
                {
                    return !meteor->isAlive();
                }
                    return false; 
                }
            );

            gameWorld->_update();
        }

        main_camera.SetUpdate();
    }

    virtual void Render()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        Draw2D::Sprite(0, 0, Window::width, Window::height, ResourceManager::GetTexture("BG:Universe"), Color::white );
        Draw2D::Sprite(0, 0, Window::width, Window::height, ResourceManager::GetTexture("BG:Star"), (Math::vec4){255, 255, 255, 40});

        static float BGrotation = 0.0f;
        BGrotation = BGrotation + 0.0005 * Time::getTime();
        Draw2D::Sprite(0.0f, 0.0f, static_cast<float>(Window::width * 2.0f),
                       static_cast<float>(Window::width * 2.0f),
                       
                       ResourceManager::GetTexture("BG:Planets"), 
                       Math::vec4(150, 150, 150, 255), BGrotation);

        
        Draw2D::BeginMode2D(main_camera.GetViewMatrix(), main_camera.GetProjectionMatrix());

        static bool Grid = false;
        if (Inputs::IsKeyPressed(Inputs::KEY_GRAVE))
        {
            Grid = !Grid;
        }
        if (Grid)
        {
            // Draw grid
            for (int i = 0; i < Window::width; i++)
                Draw2D::Line(i * GameConstants::CELL_SIZE, 0, i * GameConstants::CELL_SIZE, Window::height * GameConstants::CELL_SIZE, Color::black);
            for (int i = 0; i <= Window::height; i++)
                Draw2D::Line(0, i * GameConstants::CELL_SIZE, Window::width * GameConstants::CELL_SIZE, i * GameConstants::CELL_SIZE, Color::black);

            glLineWidth(1.0f);
            Draw2D::Line_Render();
        }

        bulletManager.Draw();
        
        // Отрисовываем всю иерархию объектов
        if (gameWorld)
            gameWorld->_draw();

       

        Draw2D::EndMode2D();

        if (gameWorld)
            gameWorld->_drawUI();
            
        Draw2D::Sprite((Rect){Inputs::x, Inputs::y, 20, 20}, ResourceManager::GetTexture("Cursor"), Color::red);
    }

    virtual void Destroy()
    {
        if (gameWorld)
        {
            delete gameWorld;
            gameWorld = nullptr;
        }
    }
};