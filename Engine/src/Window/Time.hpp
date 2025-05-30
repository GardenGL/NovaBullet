#ifndef TIME_HPP
#define TIME_HPP

#include "Window.hpp"

class Time
{
private:
    static double lastTime;
    static float deltaTime;
    static double currentTime;

public:
    static void Start();
    static void Update();
    static void Step();

    static float getDelta();
    static double getTime();
};

#endif