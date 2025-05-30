#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

// -----[ SceneManager.h ]----- //
#include <map>
#include <string>
#include <iostream>
#include <memory>



class Scene {
public:
    std::string name;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
};

class SceneManager {
public:
  
    // loads a Scene
    static void LoadScene(std::string name, Scene* s);

    static void changeScene(std::string name);

    static void  Clear();
    
private:

    static std::map<std::string, Scene*>  Scenes;
    static Scene* current_scene;

    static void MainLoop(); 
};



#endif