#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "Shader.hpp"
#include "Texture.hpp"


class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader *> Shaders;
    static std::map<std::string, Texture *> Textures;
    
    static void LoadShader(std::string ShaderFile, const char *fShaderFile, std::string name)
    {
        Shaders[name] = new Shader(ShaderFile);
    }

    static Shader *GetShader(std::string name)
    {
        return Shaders[name];
    }

    // loads (and generates) a texture from file
    static void LoadTexture(std::string file, std::string name)
    {
        Textures[name] = new Texture(file, CLAMP_TO_EDGE, LINEAR);
    }
    // retrieves a stored texture
    static Texture *GetTexture(std::string name)
    {
        return Textures[name];
    }

   
    // properly de-allocates all loaded resources
    static void Clear()
    {
        // (properly) delete all shaders
        for (auto iter : Shaders)
            delete iter.second;
        // (properly) delete all textures
        for (auto iter : Textures)
            delete iter.second;

        Shaders.clear();
        Textures.clear();
    }

private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() {}
};
// Instantiate static variables


#endif