#ifndef RECTN_HPP
#define RECTN_HPP

#include <Engine.hpp>
#include <glad/glad.h>

#include <Math/glmath.hpp>
#include <ResourceManagment/Shader.hpp>

class Rect_render
{
public:
    static void initialize();
    static void terminate();

    static void DrawRectangle(Math::mat4x4 view, Math::mat4x4 projection, float x, float y, float width, float height, float angle, Math::vec4 color = Math::vec4());

private:
    static unsigned int VBO, VAO;
    static Shader *shader;
};

#endif