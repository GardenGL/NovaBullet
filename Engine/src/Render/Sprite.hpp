#ifndef SPRITE_RENDER_H
#define SPRITE_RENDER_H

#include <Engine.hpp>

class Shader;

class Sprite_render
{
public:
  static void initialize();

  static void terminate();

  static void DrawSprite(Math::mat4x4 view, Math::mat4x4 projection, float x, float y, float width, float height, float angle, Texture *texture, Math::vec4 color);
  
private:
  static unsigned int VBO, VAO, UVBO;
  static Shader *shader;
};

#endif