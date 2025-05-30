#ifndef MATH_HPP
#define MATH_HPP
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
    class quat;

    class vec2;
    class vec3;
    class vec4;

    class mat2x2;
    class mat3x3;
    class mat4x4;

    extern float Epsilon;
    extern float PI;
    extern float Deg2Rad;
    extern float Rad2Deg;
    extern float Infinite;
    extern float NegativeInfinite;

    float Min(float a, float b);
    float Max(float a, float b);
    float Clamp(float a, float b, float t);
    float Lerp(float s, float e, float t);
    float InverseLerp(float s, float e, float t);
    float LerpAngle(float s, float e, float t);

    double Abs(double a);
    float Abs(float a);
    int Abs(int a);
    float Sqrt(float a);
    float Round(float a);
    int RoundToInt(float a);
    float Ceil(float a);
    int CeilToInt(float a);
    float Floor(float a);
    int FloorToInt(float a);

    float Sin(float a);
    float Cos(float a);
    float Tan(float a);
    float Asin(float a);
    float Acos(float a);
    float Atan(float a);
    float Atan2(float a, float b);

    float Log(float a);
    float Log10(float a);
    float Pow(float a, float b);
    float Exp(float a);

    extern vec3 left;
    extern vec3 right;
    extern vec3 up;
    extern vec3 down;
    extern vec3 forward;
    extern vec3 back;

    class vec2;
    class vec3;
    class vec4;
    class quat;

    class mat2x2;
    class mat3x3;
    class mat4x4;

    

};

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Quaternion.hpp"

#include "Matrix2x2.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

#endif