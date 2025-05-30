#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include "glmath.hpp"

namespace Math
{
    class vec3
    {
    public:
        union
        {
            struct
            {
                float x, y, z;
            };
            struct
            {
                float s, t, p;
            };
            struct
            {
                float r, g, b;
            };
            struct
            {
                float v[3];
            };
        };
        vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        ~vec3() {}
        vec3(float num) : x(num), y(num), z(num) {}
        vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        explicit vec3(const vec2 &u, float z);
        vec3(const vec3 &u) : x(u.x), y(u.y), z(u.z) {}

         vec3(const vec4 &v);

        vec3 &operator=(const vec3 &u)
        {
            x = u.x;
            y = u.y;
            z = u.z;
            return *this;
        }
        vec3 &operator=(const vec4 &u);
        vec3 &operator=(const float &u)
        {
            x = u;
            y = u;
            z = u;
            return *this;
        }
        bool operator==(const vec3 &u) const
        {
            return u.x == x && u.y == y && u.z == z;
        }
        bool operator!=(const vec3 &u) const
        {
            return u.x != x || u.y != y || u.z != z;
        }

        vec3 operator-() const  { return vec3(-x, -y, -z); }
        float *operator&() { return (float *)this; }
        vec3 &operator+=(float num)
        {
            x += num;
            y += num;
            z += num;
            return *this;
        }
        vec3 &operator+=(const vec3 &u)
        {
            x += u.x;
            y += u.y;
            z += u.z;
            return *this;
        }
        vec3 &operator-=(float num)
        {
            x -= num;
            y -= num;
            z -= num;
            return *this;
        }
        vec3 &operator-=(const vec3 &u)
        {
            x -= u.x;
            y -= u.y;
            z -= u.z;
            return *this;
        }
        vec3 &operator*=(float num)
        {
            x *= num;
            y *= num;
            z *= num;
            return *this;
        }
        vec3 &operator*=(const vec3 &u)
        {
            x *= u.x;
            y *= u.y;
            z *= u.z;
            return *this;
        }
        vec3 &operator/=(float num)
        {
            x /= num;
            y /= num;
            z /= num;
            return *this;
        }
        vec3 &operator/=(const vec3 &u)
        {
            x /= u.x;
            y /= u.y;
            z /= u.z;
            return *this;
        }
        friend vec3 operator+(const vec3 &u, float num) { return vec3(u.x + num, u.y + num, u.z + num); }
        friend vec3 operator+(float num, const vec3 &u) { return vec3(num + u.x, num + u.y, num + u.z); }
        friend vec3 operator+(const vec3 &u, const vec3 &v) { return vec3(u.x + v.x, u.y + v.y, u.z + v.z); }
        friend vec3 operator-(const vec3 &u, float num) { return vec3(u.x - num, u.y - num, u.z - num); }
        friend vec3 operator-(float num, const vec3 &u) { return vec3(num - u.x, num - u.y, num - u.z); }
        friend vec3 operator-(const vec3 &u, const vec3 &v) { return vec3(u.x - v.x, u.y - v.y, u.z - v.z); }
        friend vec3 operator*(const vec3 &u, float num) { return vec3(u.x * num, u.y * num, u.z * num); }
        friend vec3 operator*(float num, const vec3 &u) { return vec3(num * u.x, num * u.y, num * u.z); }
        friend vec3 operator*(const vec3 &u, const vec3 &v) { return vec3(u.x * v.x, u.y * v.y, u.z * v.z); }
        friend vec3 operator/(const vec3 &u, float num) { return vec3(u.x / num, u.y / num, u.z / num); }
        friend vec3 operator/(float num, const vec3 &u) { return vec3(num / u.x, num / u.y, num / u.z); }
        friend vec3 operator/(const vec3 &u, const vec3 &v) { return vec3(u.x / v.x, u.y / v.y, u.z / v.z); }
    };

    // ----------------------------------------------------------------------------------------------------------------------------

    vec3 Cross(const vec3 &u, const vec3 &v);
    float Dot(const vec3 &u, const vec3 &v);
    float SqrtMagnitude(const vec3 &u);
    float Magnitude(const vec3 &u);

    vec3 Mix(const vec3 &u, const vec3 &v, float a);
    vec3 Mix(const vec3 &u, const vec3 &v, const vec3 &a);
    vec3 Normalize(const vec3 &u);

    vec3 Reflect(const vec3 &i, const vec3 &n);
    vec3 Refract(const vec3 &i, const vec3 &n, float eta);
    // vec3 rotate(const vec3 &u, float angle, const vec3 &v);

    vec3 Max(vec3 u, vec3 v);
    vec3 Min(vec3 u, vec3 v);
    vec3 Abs(vec3 u);

    vec3 Lerp(vec3 s, vec3 e, float t);
};

#endif