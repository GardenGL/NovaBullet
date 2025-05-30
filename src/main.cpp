#include <Engine.hpp>

#include "MenuScene/MenuScene.hpp"
#include "GameScene/GameScene.hpp"

#ifdef WIN32
#include <windows.h>
#include <iostream>
#endif

void setupConsole(bool showConsole)
{
#ifdef WIN32
    if (!showConsole)
    {
        FreeConsole(); // Отключаем консоль
    }
    else
    {
        AllocConsole();                  // Создаем консоль
        freopen("CONOUT$", "w", stdout); // Перенаправляем стандартный вывод в консоль
        freopen("CONOUT$", "w", stderr); // Перенаправляем стандартный вывод ошибок в консоль
    }
#endif
}

int main(int argc, char *argv[])
{
#ifdef WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif

#ifdef WIN32
    bool showConsole = false;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--showconsole") == 0)
        {
            showConsole = true;
            break;
        }
    }
    setupConsole(showConsole);
#endif

    Engine::Initialize(1600, 900, "Sandbox Game");

    ResourceManager::LoadTexture("assets/player/Cursor.png", "Cursor");
    ResourceManager::LoadTexture("assets/player/ship_L.png", "SpaceShip");
    ResourceManager::LoadTexture("assets/player/Bullet.png", "bullet");

    ResourceManager::LoadTexture("assets/background/universe.png", "BG:Universe");
    ResourceManager::LoadTexture("assets/background/planets.png", "BG:Planets");
    ResourceManager::LoadTexture("assets/background/star.png", "BG:Star");
    ResourceManager::LoadTexture("assets/background/station_B.png", "Logo");

    ResourceManager::LoadTexture("assets/meteors/0.png", "meteor:0");
    ResourceManager::LoadTexture("assets/meteors/1.png", "meteor:1");
    ResourceManager::LoadTexture("assets/meteors/2.png", "meteor:2");
    ResourceManager::LoadTexture("assets/meteors/3.png", "meteor:3");
    ResourceManager::LoadTexture("assets/meteors/4.png", "meteor:4");
    ResourceManager::LoadTexture("assets/meteors/5.png", "meteor:5");
    ResourceManager::LoadTexture("assets/meteors/6.png", "meteor:6");
    ResourceManager::LoadTexture("assets/meteors/7.png", "meteor:7");

    ResourceManager::LoadTexture("assets/enemy/0.png", "enemy:0");
    ResourceManager::LoadTexture("assets/enemy/1.png", "enemy:1");
    ResourceManager::LoadTexture("assets/enemy/2.png", "enemy:2");
    ResourceManager::LoadTexture("assets/enemy/3.png", "enemy:3");
    ResourceManager::LoadTexture("assets/enemy/4.png", "enemy:4");

    SceneManager::LoadScene("main_menu", new MenuScene());
    SceneManager::LoadScene("game_scene", new GameScene());

    SceneManager::changeScene("main_menu");

    log_info("Exit");
    Engine::terminate();
    return 0;
}