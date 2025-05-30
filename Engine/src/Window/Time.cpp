#include "Time.hpp"

#include <GLFW/glfw3.h>

float Time::deltaTime = 0;
double Time::currentTime = 0;
double Time::lastTime = 0;

void Time::Start()
{
    deltaTime = 0.0f;
    lastTime = glfwGetTime();
}

void Time::Update()
{
    currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);
}

void Time::Step()
{
    lastTime = glfwGetTime();
    lastTime = currentTime;
}

float Time::getDelta()
{
    return (float)deltaTime;
}

double Time::getTime()
{
    return lastTime;
}