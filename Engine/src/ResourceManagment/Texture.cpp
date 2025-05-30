#include "Texture.hpp"
#include <Engine.hpp>
#include <glad/glad.h>
#include <Window/log.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(std::string file, TextureWrap textWrap, TextureFilter textFilter)
{
    this->file = file;
    this->textWrap = textWrap;
    this->textFilter = textFilter;

    unsigned char *data = stbi_load(file.c_str(), &width, &height, &numcomponents, STBI_rgb_alpha);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textFilter);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        log_info("Load texture: %s", file.c_str());
    }
    else
    {
        log_error("Failed to load image: %s", file.c_str());
    }

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}