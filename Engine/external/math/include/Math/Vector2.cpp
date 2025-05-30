#include "Vector2.hpp"
namespace Math
{
    float Dot(const vec2 &u, const vec2 &v)
    {
        return u.x * v.x + u.y * v.y;
    }

    float SqrtMagnitude(const vec2 &u)
    {
        return Math::Sqrt(Magnitude(u));
    }

    float Magnitude(const vec2 &u)
    {
        return Dot(u, u);
    }

    vec2 Mix(const vec2 &u, const vec2 &v, float a)
    {
        return u * (1.0f - a) + v * a;
    }

    vec2 Normalize(const vec2 &u)
    {
        return u / sqrt(u.x * u.x + u.y * u.y);
    }

    vec2 Reflect(const vec2 &i, const vec2 &n)
    {
        return i - 2.0f * Dot(n, i) * n;
    }

    vec2 Refract(const vec2 &i, const vec2 &n, float eta)
    {
        vec2 r;

        float ndoti = Dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

        if (k >= 0.0f)
        {
            r = eta * i - n * (eta * ndoti + sqrt(k));
        }

        return r;
    }

    vec2 Rotate(const vec2 &u, float angle)
    {
        angle = angle / 180.0f * (float)M_PI;

        float c = cos(angle), s = sin(angle);

        return vec2(u.x * c - u.y * s, u.x * s + u.y * c);
    }

};