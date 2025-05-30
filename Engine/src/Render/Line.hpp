#ifndef LINE_HPP
#define LINE_HPP

#include <ResourceManagment/Shader.hpp>
#include <Math/glmath.hpp>
#include <vector>

class LineRender
{
public:
    static void initialize();
    static void terminate();

    static void DrawLine(Math::vec2 start, Math::vec2 end, Math::vec4 color);

    static void Render(Math::mat4x4 view, Math::mat4x4 projection);

private:
    static std::vector<Math::vec2> Lines_list;
    static std::vector<Math::vec4> Color_Lines_list;
    static unsigned int VAO, VBO, CBO;
    static Shader *shader;
};

#endif