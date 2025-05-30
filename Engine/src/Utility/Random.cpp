#include "Random.hpp"

// Инициализация генератора случайных чисел
std::mt19937 Random::m_Engine(std::random_device{}());

void Random::SetSeed(int seed)
{
    m_Engine.seed(seed);
}

float Random::Float(float min, float max)
{
    if (min >= max)
        throw std::invalid_argument("min must be less than max");
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_Engine);
}

int Random::Int(int min, int max)
{
    if (min >= max)
        throw std::invalid_argument("min must be less than max");
    std::uniform_int_distribution<int> distribution(min, max - 1);
    return distribution(m_Engine);
}