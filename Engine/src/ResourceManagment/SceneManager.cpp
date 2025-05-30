
// -----[ SceneManager.h ]----- //
#include "Shader.hpp"
#include "Texture.hpp"

#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include <Window/Inputs.hpp>
#include <Window/Window.hpp>
#include <Window/Time.hpp>

Scene *SceneManager::current_scene = nullptr;
std::map<std::string, Scene *> SceneManager::Scenes;

void SceneManager::LoadScene(std::string name, Scene *s)
{
    s->name = name;
    Scenes[name] = s;
}

void SceneManager::changeScene(std::string name)
{
    Window::swapBuffers();
    Inputs::pullEvents();

    if (current_scene != nullptr)
    {
        current_scene->Destroy();
        //ResourceManager::Clear();
    }

    current_scene = Scenes[name];
    current_scene->Start();

    MainLoop();
}

void SceneManager::Clear()
{
    for (auto iter : Scenes)
        delete iter.second;
    delete current_scene;
}

void SceneManager::MainLoop()
{
    Time::Start();

    
    

    
    while (!Window::isShouldClose() && current_scene != nullptr)
    {
        Time::Update();

        current_scene->Update();
        current_scene->Render();

        Window::swapBuffers();
        Inputs::pullEvents();
        
        Time::Step();
    }
}