#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <string>

enum TextureFilter
{
    LINEAR = GL_LINEAR,
    NEAREST = GL_NEAREST
};

enum TextureWrap
{
    REPEAT = GL_REPEAT,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
};

class Texture
{
public:
    Texture(std::string file, TextureWrap textWrap, TextureFilter textFilter);

    ~Texture();

    void Bind();
    void Unbind();

    int getWidth() { return width; }
    int getHeight() { return height; }
    
private:

    std::string file;
    
    int width, height, numcomponents;
    unsigned int textureID;

    TextureWrap textWrap = REPEAT;
    TextureFilter textFilter = NEAREST;
};

#endif // TEXTURE_HPP
