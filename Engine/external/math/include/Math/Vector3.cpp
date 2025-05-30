#include "Vector3.hpp"
#include "Vector4.hpp"
namespace Math
{
    vec3::vec3(const vec4 &v)
    {

        x = v.x;
        y = v.y;
        z = v.z;
    }
    vec3::vec3(const vec2 &u, float _z)
    {
        x = u.x;
        y = u.y;
        z = _z;
    }
    vec3 &vec3::operator=(const vec4 &u)
    {
        x = u.x;
        y = u.y;
        z = u.z;
        return *this;
    }
    vec3 Cross(const vec3 &u, const vec3 &v)
    {
        return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    }

    float Dot(const vec3 &u, const vec3 &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    float SqrtMagnitude(const vec3 &u)
    {
        return Math::Sqrt(Magnitude(u));
    }

    float Magnitude(const vec3 &u)
    {
        return Dot(u, u);
    }

    vec3 Mix(const vec3 &u, const vec3 &v, float a)
    {
        return u * (1.0f - a) + v * a;
    }
    vec3 Mix(const vec3 &u, const vec3 &v, const vec3 &a)
    {
        return (vec3(1.0f) - a) * u + a * v;
    }

    vec3 Normalize(const vec3 &u)
    {
        return u / Sqrt(Dot(u, u));
    }

    vec3 Reflect(const vec3 &i, const vec3 &n)
    {
        return i - 2.0f * Dot(n, i) * n;
    }

    vec3 Refract(const vec3 &i, const vec3 &n, float eta)
    {
        vec3 r;

        float ndoti = Dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

        if (k >= 0.0f)
        {
            r = eta * i - n * (eta * ndoti + sqrt(k));
        }

        return r;
    }

    // vec3 rotate(const vec3 &u, float angle, const vec3 &v)
    //{
    //   return *(vec3 *)&(rotate(angle, v) * vec4(u, 1.0f));
    //}

    vec3 Max(vec3 u, vec3 v)
    {
        return vec3(Max(u.x, v.x), Max(u.y, v.y), Max(u.z, v.z));
    }
    vec3 Min(vec3 u, vec3 v)
    {
        return vec3(Min(u.x, v.x), Min(u.y, v.y), Min(u.z, v.z));
    }
    vec3 Abs(vec3 u)
    {
        return vec3(Abs(u.x), Abs(u.y), Abs(u.z));
    }

    vec3 Lerp(vec3 s, vec3 e, float t)
    {
        return s * (1 - t) + e * t;
    }

};