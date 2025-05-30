#include <Engine.hpp>
#include <glad/glad.h>
#include "Sprite.hpp"
#include "ResourceManagment/Shader.hpp"

void Sprite_render::initialize()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &UVBO);

  Math::vec2 arr[] = {{1, 0}, {0, 0}, {1, 1}, {1, 1}, {0, 0}, {0, 1}};
  Math::vec2 uv[] = {{1, 0}, {0, 0}, {1, 1}, {1, 1}, {0, 0}, {0, 1}};

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Math::vec2), NULL);

  glBindBuffer(GL_ARRAY_BUFFER, UVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Math::vec2), NULL);

  std::string VS = R"glsl(
    #version 330 core

    layout(location=0)in vec2 point;
    layout(location=1)in vec2 uv;

    uniform mat4 model;

    out vec2 vertex_uv;

    void main()
    {
      gl_Position = model * vec4(point.x,point.y,0.0,1.0);
      vertex_uv=uv;
    }
  )glsl";
  std::string FS = R"glsl(
    #version 330 core

    out vec4 finalcolor;
    in vec2 vertex_uv;
    uniform sampler2D sprite;
    uniform vec4 color;

    void main()
    { 
      finalcolor = color * texture(sprite,vertex_uv);   
      if(finalcolor.a == 0.0f){discard;}
    }
  )glsl";

  shader = new Shader(VS, FS);
}

void Sprite_render::terminate()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &UVBO);
  delete shader;
}

void Sprite_render::DrawSprite(Math::mat4x4 view, Math::mat4x4 projection, float x, float y, float width, float height, float angle, Texture *texture, Math::vec4 color)
{
  glDisable(GL_DEPTH_TEST);
  shader->Bind();
  texture->Bind();

  Math::mat4x4 model = Math::mat4x4();
  model = model * Math::Translate(Math::vec3(x, y, 0.0f));

  model = model * Math::Translate(Math::vec3(0.5f * width, 0.5f * height, 0.0f));
  model = model * Math::Rotate(angle, Math::vec3(0.0f, 0.0f, 1.0f));
  model = model * Math::Translate(Math::vec3(-0.5f * width, -0.5f * height, 0.0f));

  model = model * Math::Scale(Math::vec3(width, height, 1.0f));
  
  Math::mat4x4 PVM = Math::mat4x4();
  PVM = PVM * projection * view * model;
  shader->SetMatrix4("model", PVM );

  shader->SetColor("color", color);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  shader->Unbind();
  texture->Unbind();
  glEnable(GL_DEPTH_TEST);
}
unsigned int Sprite_render::VBO, Sprite_render::VAO, Sprite_render::UVBO;
Shader *Sprite_render::shader;