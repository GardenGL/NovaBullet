#include "Vector4.hpp"
namespace Math
{
    vec4::vec4(const vec2 &u, float _z, float _w) : x(u.x), y(u.y), z(z), w(w)
    {
        x = u.x;
        y = u.y;
        z = _z;
        w = _w;
    }
    vec4::vec4(const vec3 &u, float _w) : x(u.x), y(u.y), z(u.z), w(w)
    {
        x = u.x;
        y = u.y;
        z = u.z;
        w = _w;
    }
    float Dot(const vec4 &u, const vec4 &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
    }
};