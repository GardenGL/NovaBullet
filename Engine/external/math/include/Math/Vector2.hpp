#ifndef VECTOR2_HPP
#define VECTOR2_HPP
#include "glmath.hpp"
namespace Math
{
    class vec2
    {
    public:
        union
        {
            struct
            {
                float x, y;
            };
            struct
            {
                float s, t;
            };
            struct
            {
                float r, g;
            };
            struct
            {
                float v[2];
            };
        };
        vec2() : x(0.0f), y(0.0f) {}
        ~vec2() {}
        vec2(float num) : x(num), y(num) {}
        vec2(float x, float y) : x(x), y(y) {}
        vec2(const vec2 &u) : x(u.x), y(u.y) {}
        vec2 &operator=(const vec2 &u)
        {
            x = u.x;
            y = u.y;
            return *this;
        }
        bool operator==(const vec2 &u) const
        {
            return u.x == x && u.y == y;
        }

        vec2 operator-() { return vec2(-x, -y); }
        float *operator&() { return (float *)this; };
        vec2 &operator+=(float num)
        {
            x += num;
            y += num;
            return *this;
        }
        vec2 &operator+=(const vec2 &u)
        {
            x += u.x;
            y += u.y;
            return *this;
        }
        vec2 &operator-=(float num)
        {
            x -= num;
            y -= num;
            return *this;
        }
        vec2 &operator-=(const vec2 &u)
        {
            x -= u.x;
            y -= u.y;
            return *this;
        }
        vec2 &operator*=(float num)
        {
            x *= num;
            y *= num;
            return *this;
        }
        vec2 &operator*=(const vec2 &u)
        {
            x *= u.x;
            y *= u.y;
            return *this;
        }
        vec2 &operator/=(float num)
        {
            x /= num;
            y /= num;
            return *this;
        }
        vec2 &operator/=(const vec2 &u)
        {
            x /= u.x;
            y /= u.y;
            return *this;
        }
        friend vec2 operator+(const vec2 &u, float num) { return vec2(u.x + num, u.y + num); }
        friend vec2 operator+(float num, const vec2 &u) { return vec2(num + u.x, num + u.y); }
        friend vec2 operator+(const vec2 &u, const vec2 &v) { return vec2(u.x + v.x, u.y + v.y); }
        friend vec2 operator-(const vec2 &u, float num) { return vec2(u.x - num, u.y - num); }
        friend vec2 operator-(float num, const vec2 &u) { return vec2(num - u.x, num - u.y); }
        friend vec2 operator-(const vec2 &u, const vec2 &v) { return vec2(u.x - v.x, u.y - v.y); }
        friend vec2 operator*(const vec2 &u, float num) { return vec2(u.x * num, u.y * num); }
        friend vec2 operator*(float num, const vec2 &u) { return vec2(num * u.x, num * u.y); }
        friend vec2 operator*(const vec2 &u, const vec2 &v) { return vec2(u.x * v.x, u.y * v.y); }
        friend vec2 operator/(const vec2 &u, float num) { return vec2(u.x / num, u.y / num); }
        friend vec2 operator/(float num, const vec2 &u) { return vec2(num / u.x, num / u.y); }
        friend vec2 operator/(const vec2 &u, const vec2 &v) { return vec2(u.x / v.x, u.y / v.y); }
    };

    // ----------------------------------------------------------------------------------------------------------------------------

    float Dot(const vec2 &u, const vec2 &v);
    float Magnitude(const vec2 &u);
    float SqrtMagnitude(const vec2 &u);
    vec2 Mix(const vec2 &u, const vec2 &v, float a);
    vec2 Normalize(const vec2 &u);
    vec2 Reflect(const vec2 &i, const vec2 &n);
    vec2 Refract(const vec2 &i, const vec2 &n, float eta);
    vec2 Rotate(const vec2 &u, float angle);
};
#endif