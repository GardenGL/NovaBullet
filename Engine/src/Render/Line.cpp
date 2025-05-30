

#include <Engine.hpp>
#include <glad/glad.h>
#include "Line.hpp"

// Instantiate static variables
std::vector<Math::vec2> LineRender::Lines_list;
std::vector<Math::vec4> LineRender::Color_Lines_list;
unsigned int LineRender::VAO, LineRender::VBO, LineRender::CBO;
Shader *LineRender::shader;

void LineRender::initialize()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);

    std::string VS = R"glsl(
            #version 330 core
 
            layout (location = 0) in vec2 aPos;
            layout (location = 1) in vec4 acolor;

            uniform mat4 model;

            out vec4 color;

            void main()
            {
			    gl_Position = model * vec4(aPos.x, aPos.y, 0.0 , 1.0);
			    color = acolor;
            }   
        )glsl";

    std::string FS = R"glsl(
            #version 330 core

            out vec4 FragColor;
            in vec4 color;

            void main()
            {
                FragColor = color;
            }
        )glsl";

    shader = new Shader(VS, FS);
}
void LineRender::terminate()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &CBO);
    delete shader;
}

void LineRender::DrawLine(Math::vec2 start, Math::vec2 end, Math::vec4 color)
{
    color = color / 255.0f;

    Lines_list.push_back(start);
    Color_Lines_list.push_back(color);

    Lines_list.push_back(end);
    Color_Lines_list.push_back(color);
}

void LineRender::Render(Math::mat4x4 view, Math::mat4x4 projection)
{
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Lines_list.size() * sizeof(Math::vec2), Lines_list.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, Color_Lines_list.size() * sizeof(Math::vec4), Color_Lines_list.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Math::mat4x4 PV = Math::mat4x4();
    PV = PV * projection;
    PV = PV * view;

    shader->Bind();
    shader->SetMatrix4("model", PV );
    glDrawArrays(GL_LINES, 0, (int)Lines_list.size());
    shader->Unbind();

    Lines_list.clear();
    Color_Lines_list.clear();
    glEnable(GL_DEPTH_TEST);
}
