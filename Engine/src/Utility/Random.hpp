#pragma once

#include <random>
#include <stdexcept>

#undef max

class Random
{
private:
    static std::mt19937 m_Engine;

    Random() = delete; // Запрещаем создание экземпляров класса

public:
    static void SetSeed(int seed);
    static float Float(float min, float max);
    static int Int(int min, int max);
};