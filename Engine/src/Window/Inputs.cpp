#include "Inputs.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (Inputs::_cursor_started)
	{
		Inputs::deltaX += xpos - Inputs::x;
		Inputs::deltaY += ypos - Inputs::y;
	}
	else
	{
		Inputs::_cursor_started = true;
	}
	Inputs::x = (float)xpos;
	Inputs::y = (float)ypos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		Inputs::_keys[1024 + button] = true;
		Inputs::_frames[1024 + button] = Inputs::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Inputs::_keys[1024 + button] = false;
		Inputs::_frames[1024 + button] = Inputs::_current;
	}
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		Inputs::_keys[key] = true;
		Inputs::_frames[key] = Inputs::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Inputs::_keys[key] = false;
		Inputs::_frames[key] = Inputs::_current;
	}
}

void window_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window::width = width;
	Window::height = height;
}

namespace Inputs {

int initialize()
{
	GLFWwindow *window = Window::window;
	_keys = new bool[1032];
	_frames = new unsigned int[1032];

	memset(_keys, false, 1032 * sizeof(bool));
	memset(_frames, 0, 1032 * sizeof(unsigned int));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	return 0;
}

void SetCursorMode(bool mode){
	if(mode){

		float x = Inputs::x;
		float y = Inputs::y;

		glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		setCursorPos(x,y);
		
		Inputs::_cursor_locked = false;
	}
	else {
		Inputs::_cursor_locked = true;
		glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void setCursorPos(float width, float height){
	glfwSetCursorPos(Window::window, width, height );
}

void toggleCursor()
{
	_cursor_locked = !_cursor_locked;
	SetCursorMode(_cursor_locked ? false : true);
}

void terminate()
{
	delete[] _keys;
	delete[] _frames;
}

void pullEvents()
{
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}

bool IsKeyDown(int keycode)
{

	if (keycode < 0 || keycode >= 1032)
		return false;

	return _keys[keycode];
}

bool IsKeyPressed(int keycode)
{

	if (keycode < 0 || keycode >= 1032)
		return false;

	return _keys[keycode] == 1 && _frames[keycode] == _current;
}

bool IsKeyReleased(int keycode)
{

	if (keycode < 0 || keycode >= 1032)
		return true;

	return _keys[keycode] == 0 && _frames[keycode] == _current;
}

}