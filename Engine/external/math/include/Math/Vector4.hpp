#ifndef VECTOR4_HPP
#define VECTOR4_HPP
#include "glmath.hpp"
namespace Math
{
    class vec4
    {
    public:
        union
        {
            struct
            {
                float x, y, z, w;
            };
            struct
            {
                float s, t, p, q;
            };
            struct
            {
                float r, g, b, a;
            };
            struct
            {
                float v[4];
            };
        };
        vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        ~vec4() {}
        vec4(float num) : x(num), y(num), z(num), w(num) {}
        vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        explicit vec4(const vec2 &u, float _z, float _w);
        explicit vec4(const vec3 &u, float _w);
        vec4(const vec4 &u) : x(u.x), y(u.y), z(u.z), w(u.w) {}
        vec4 &operator=(const vec4 &u)
        {
            x = u.x;
            y = u.y;
            z = u.z;
            w = u.w;
            return *this;
        }
        vec4 operator-() { return vec4(-x, -y, -z, -w); }
        float *operator&() { return (float *)this; }
        vec4 &operator+=(float num)
        {
            x += num;
            y += num;
            z += num;
            w += num;
            return *this;
        }
        vec4 &operator+=(const vec4 &u)
        {
            x += u.x;
            y += u.y;
            z += u.z;
            w += u.w;
            return *this;
        }
        vec4 &operator-=(float num)
        {
            x -= num;
            y -= num;
            z -= num;
            w -= num;
            return *this;
        }
        vec4 &operator-=(const vec4 &u)
        {
            x -= u.x;
            y -= u.y;
            z -= u.z;
            w -= u.w;
            return *this;
        }
        vec4 &operator*=(float num)
        {
            x *= num;
            y *= num;
            z *= num;
            w *= num;
            return *this;
        }
        vec4 &operator*=(const vec4 &u)
        {
            x *= u.x;
            y *= u.y;
            z *= u.z;
            w *= u.w;
            return *this;
        }
        vec4 &operator/=(float num)
        {
            x /= num;
            y /= num;
            z /= num;
            w /= num;
            return *this;
        }
        vec4 &operator/=(const vec4 &u)
        {
            x /= u.x;
            y /= u.y;
            z /= u.z;
            w /= u.w;
            return *this;
        }
        friend vec4 operator+(const vec4 &u, float num) { return vec4(u.x + num, u.y + num, u.z + num, u.w + num); }
        friend vec4 operator+(float num, const vec4 &u) { return vec4(num + u.x, num + u.y, num + u.z, num + u.w); }
        friend vec4 operator+(const vec4 &u, const vec4 &v) { return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w); }
        friend vec4 operator-(const vec4 &u, float num) { return vec4(u.x - num, u.y - num, u.z - num, u.w - num); }
        friend vec4 operator-(float num, const vec4 &u) { return vec4(num - u.x, num - u.y, num - u.z, num - u.w); }
        friend vec4 operator-(const vec4 &u, const vec4 &v) { return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w); }
        friend vec4 operator*(const vec4 &u, float num) { return vec4(u.x * num, u.y * num, u.z * num, u.w * num); }
        friend vec4 operator*(float num, const vec4 &u) { return vec4(num * u.x, num * u.y, num * u.z, num * u.w); }
        friend vec4 operator*(const vec4 &u, const vec4 &v) { return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w); }
        friend vec4 operator/(const vec4 &u, float num) { return vec4(u.x / num, u.y / num, u.z / num, u.w / num); }
        friend vec4 operator/(float num, const vec4 &u) { return vec4(num / u.x, num / u.y, num / u.z, num / u.w); }
        friend vec4 operator/(const vec4 &u, const vec4 &v) { return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w); }
    };
    float Dot(const vec4 &u, const vec4 &v);
};


#endif