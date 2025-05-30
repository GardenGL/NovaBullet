
#include "Font.hpp"
#include "FontLib.h"
#include <iostream>
#include "../../Window/log.hpp"

FONScontext *fons;
int normalfont;


void InitFont(int width, int height, const char *path)
{
    normalfont = FONS_INVALID;
    fons = glfonsCreate(width, height, FONS_ZERO_TOPLEFT);
    normalfont = fonsAddFont(fons, "sans", path);
    if (normalfont < 0)
    {
        log_error("Font loading error: %s \n", path);
    }
    else
    {
        log_info("Load font: %s", path);
    }
}

void DrawTextF(std::string text, float x, float y, float size, int align, Math::vec4 color)
{
    fontShader->Bind();

    Math::mat4x4 projection = Math::Ortho(0.0f, (float)Window::width , (float)Window::height, 0.0f, 1.0f, -1.0f);
    fontShader->SetMatrix4("projection", projection);

    glDisable(GL_DEPTH_TEST);
    fontShader->SetVector4("textColor", color / 255.0f);
    fonsSetAlign(fons, align);
    fontDrawText(normalfont, fons, text.c_str(), x, y, size, NULL);
    glEnable(GL_DEPTH_TEST);

    fontShader->Unbind();
}
