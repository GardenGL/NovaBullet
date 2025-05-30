#pragma once
#include "Constants.hpp"
#include <Math/glmath.hpp>

namespace Utils
{
    inline bool isPointInMap(int x, int y)
    {
        return x >= 0 && y >= 0 && x < GameConstants::GRID_WIDTH && y < GameConstants::GRID_HEIGHT;
    }

    template <typename T>
    inline T clamp(T value, T min, T max)
    {
        return (value < min) ? min : (value > max) ? max
                                                   : value;
    }

    template <typename T>
    constexpr T radians(T degrees)
    {
        static_assert(std::is_floating_point_v<T>, "'radians' only accept floating-point input");
        return degrees * (3.14159265358979323846 / 180.0);
    }

    #define RAD2DEG 360 / (Math::PI * 2)
    float Get_Angle_To_Point(Math::vec2 V1, Math::vec2 V2)
    {
        Math::vec2 V3 = V2 - V1;

        return std::atan2(-V3.y, -V3.x) * RAD2DEG;
    }
}

// A* Pathfinding node
struct PathNode
{
    int x, y;
    float g, h, f;
    PathNode *parent;

    PathNode(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}
};

// Rectangle structure
struct RectangleF
{
    double x, y, width, height;
};