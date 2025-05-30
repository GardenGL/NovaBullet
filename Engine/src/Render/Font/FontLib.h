#ifndef FONTLIB_H
#define FONTLIB_H
#pragma once
#include <Engine.hpp>

#include <string>

#define FONTSTASH_IMPLEMENTATION // Expands implementation
#include <STB/fontstash.h>

#include <GLAD/glad.h>

std::string VS = R"glsl(
        				#version 330 core
				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec2 tcoord;
				out vec2 TexCoords;

				uniform mat4 projection;

				void main()
				{
					gl_Position = projection * vec4(vertex, 0.0, 1.0);
					TexCoords = tcoord;
				} 
    )glsl";
std::string FS = R"glsl(
				#version 330 core
				in vec2 TexCoords;
				out vec4 color;

				uniform sampler2D text;
				uniform vec4 textColor;

				void main()
				{
					vec4 sampled = textColor * vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
					color = textColor * sampled;
				}
    )glsl";


 std::string vs3D = R"glsl(
#version 330 core

layout (location = 0) in vec2 vert;
layout (location = 1) in vec2 uv;

uniform vec3 pos;          // Позиция солнца
uniform vec2 scaleF;       // Масштаб
uniform mat4 projection;   // Матрица проекции
uniform mat4 view;         // Матрица вида

out vec2 fragOffset;

void main()
{
    fragOffset = uv;

    // Извлечение осей из матрицы view
    vec3 cameraRightWorld = normalize(vec3(view[0][0], view[1][0], view[2][0])); // Ось X (Right)
    vec3 cameraUpWorld = normalize(vec3(view[0][1], view[1][1], view[2][1]));    // Ось Y (Up)
    
    // Построение позиции с учётом ориентации камеры
    vec3 axisX = scaleF.x * vert.x * cameraRightWorld;
    vec3 axisY = scaleF.y * vert.y * cameraUpWorld; // vec3(0.0, 1.0, 0.0);

    vec3 positionWorld = pos + axisX + -axisY;

    // Применение матриц проекции и вида
    gl_Position = projection * view * vec4(positionWorld, 1.0);
}

)glsl";

    std::string fs3D = R"glsl(
#version 330 core
out vec4 finalcolor;
in vec2 fragOffset;
uniform sampler2D text;
uniform vec4 baseColor;

void main() {
    finalcolor = baseColor * vec4(1.0, 1.0, 1.0, texture(text, fragOffset).r);
}
)glsl";

Shader *fontShader;
Shader *font3DShader;

struct GLFONScontext
{
	GLuint tex;
	GLuint VAO, VBOvert, VBOtex;
	int width, height;
};
typedef struct GLFONScontext GLFONScontext;

unsigned int glfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r) | (g << 8) | (b << 16) | (a << 24);
}

static int glfons__renderCreate(void *userPtr, int width, int height)
{
	fontShader = new Shader(VS, FS);
	font3DShader = new Shader(vs3D, fs3D);
	
	GLFONScontext *gl = (GLFONScontext *)userPtr;
	// Create may be called multiple times, delete existing texture.
	if (gl->tex != 0)
	{
		glDeleteTextures(1, &gl->tex);
		gl->tex = 0;
	}
	glGenTextures(1, &gl->tex);
	if (!gl->tex)
		return 0;
	gl->width = width;
	gl->height = height;
	glBindTexture(GL_TEXTURE_2D, gl->tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, gl->width, gl->height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x2900);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x2900);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return 1;
}

static int glfons__renderResize(void *userPtr, int width, int height)
{
	// Reuse create to resize too.
	return glfons__renderCreate(userPtr, width, height);
}

static void glfons__renderUpdate(void *userPtr, int *rect, const unsigned char *data)
{
	GLFONScontext *gl = (GLFONScontext *)userPtr;
	int w = rect[2] - rect[0];
	int h = rect[3] - rect[1];

	if (gl->tex == 0)
		return;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl->tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, gl->width);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect[0]);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, rect[1]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, rect[0], rect[1], w, h, GL_RED, GL_UNSIGNED_BYTE, data);
}

static void glfons__renderDraw(void *userPtr, const float *verts, const float *tcoords, const unsigned int *colors, int nverts)
{
	GLFONScontext *gl = (GLFONScontext *)userPtr;

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gl->VAO);

	if (gl->tex == 0)
		return;

	glBindTexture(GL_TEXTURE_2D, gl->tex);

	glBindBuffer(GL_ARRAY_BUFFER, gl->VBOvert);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nverts * 2, verts);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0); // vertex attr

	glBindBuffer(GL_ARRAY_BUFFER, gl->VBOtex);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * nverts * 2, tcoords);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0); // tcoord attr

	glDrawArrays(GL_TRIANGLES, 0, nverts); ////////////////////////////////////////////////////////////THERE IS GL_DRAW_ARRAYS
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

static void glfons__renderDelete(void *userPtr)
{
	GLFONScontext *gl = (GLFONScontext *)userPtr;
	if (gl->tex != 0)
		glDeleteTextures(1, &gl->tex);
	gl->tex = 0;
	free(gl);
}

//////////////////////////////////////////////////////////////////////////

GLFONScontext *LoadShaderFont(int screenwidth, int screenheight)
{
	GLFONScontext *gl;
	gl = (GLFONScontext *)malloc(sizeof(GLFONScontext));

	memset(gl, 0, sizeof(GLFONScontext));

	glGenVertexArrays(1, &gl->VAO);
	glGenBuffers(1, &gl->VBOvert);
	glGenBuffers(1, &gl->VBOtex);

	glBindVertexArray(gl->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, gl->VBOvert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * FONS_VERTEX_COUNT * 2, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, gl->VBOtex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * FONS_VERTEX_COUNT * 2, NULL, GL_DYNAMIC_DRAW);

	return gl;
}

FONScontext *glfonsCreate(int screenwidth, int screenheight, int flags)
{
	FONSparams params;
	GLFONScontext *gl = LoadShaderFont(screenwidth, screenheight);

	memset(&params, 0, sizeof(params));
	params.width = screenwidth;
	params.height = screenheight;
	params.flags = (unsigned char)flags;
	params.renderCreate = glfons__renderCreate;
	params.renderResize = glfons__renderResize;
	params.renderUpdate = glfons__renderUpdate;
	params.renderDraw = glfons__renderDraw;
	params.renderDelete = glfons__renderDelete;
	params.userPtr = gl;

	return fonsCreateInternal(&params);
}

#endif