#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"

#include <windows.h>
#include "Inputs.hpp"
#include "log.hpp"

GLFWwindow* Window::window;
int Window::width = 0;
int Window::height = 0;

#ifdef WIN32
#include <Windows.h>

void configure_encoding()
{
    // set utf-8 encoding to console output
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
}
#else
void configure_encoding()
{
}
#endif

void error_callback(int error, const char *description)
{
	log_error("%s", description);
}

int Window::initialize(int width, int height, const char* title){
	
	configure_encoding();
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (window == nullptr){
		log_error("Failed to create GLFW Window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        log_error("Failed to initialize GLAD");;
        return -1;
    }

	glViewport(0,0, width, height);

	Window::width = width;
	Window::height = height;

	// print which version of OpenGL started
    {
        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *version = glGetString(GL_VERSION);
        log_info("Renderer: %s", renderer);
        log_info("OpenGL version supported %s", version);
    }
	glfwSwapInterval(1);
	log_info("VSync: ON");
	
	glfwSetWindowSizeLimits(window, 1280, 720, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSetWindowAspectRatio(window, 16, 9);
	glfwSetErrorCallback(error_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	{
		glEnable(GL_CULL_FACE);
		glDepthFunc(GL_LEQUAL);
    	glEnable(GL_BLEND);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glfwSetWindowPos(window,0 + 100,0 + 100);
	
	return 0;
}

void Window::viewport(int x, int y, int width, int height){
	glViewport(x, y, width, height);
}



void Window::terminate(){
	glfwTerminate();
}

bool Window::isShouldClose(){
	return glfwWindowShouldClose(window);
}

void Window::Close(){
	glfwSetWindowShouldClose(window, true);
}

void Window::swapInterval(int interval){
	glfwSwapInterval(interval);
}

void Window::swapBuffers(){
	glfwSwapBuffers(window);
}