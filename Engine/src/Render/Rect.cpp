#include "Rect.hpp"

unsigned int Rect_render::VAO, Rect_render::VBO;
Shader *Rect_render::shader;

void Rect_render::terminate()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
}

void Rect_render::initialize()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    Math::vec2 arr[] = {{1, 0}, {0, 0}, {1, 1}, {1, 1}, {0, 0}, {0, 1}};

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Math::vec2), NULL);

    std::string VS = R"glsl(
            #version 330 core
            layout (location = 0) in vec3 vert;

            uniform mat4 model;

            void main()
            {
             gl_Position = model * vec4(vert.x, vert.y, 0.0, 1.0);
            }
        )glsl";

    std::string FS = R"glsl(     
            #version 330 core
            out vec4 finalcolor;

            uniform vec4 color;

            void main() {
                finalcolor = color;
            }
        )glsl";

    shader = new Shader(VS, FS);
}

void Rect_render::DrawRectangle(Math::mat4x4 view, Math::mat4x4 projection, float x, float y, float width, float height, float angle, Math::vec4 color)
{
    glDisable(GL_DEPTH_TEST);
    shader->Bind();


    Math::mat4x4 PVM = Math::mat4x4();

    //P
    PVM = PVM * projection;
    
    PVM = PVM * view;
    //M
    PVM = PVM * Math::Translate(Math::vec3(x,y , 0.0f));  
    PVM = PVM * Math::Translate(Math::vec3(0.5f * width, 0.5f * height, 0.0f)); 
    PVM = PVM * Math::Rotate(angle, Math::vec3(0.0f, 0.0f, 1.0f));
    PVM = PVM * Math::Translate(Math::vec3(-0.5f * width, -0.5f * height, 0.0f)); 
    PVM = PVM * Math::Scale(Math::vec3(width, height , 1.0f));
   
    shader->SetMatrix4("model", PVM);

    shader->SetColor("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    shader->Unbind();

    glEnable(GL_DEPTH_TEST);
}