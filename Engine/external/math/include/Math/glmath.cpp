#include "glmath.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
namespace Math
{
    float Epsilon = 0.000001f;
    float PI = 3.14159265358979f;
    float Deg2Rad = (PI * 2) / 360;
    float Rad2Deg = 360 / (PI * 2);
    float Infinite = FLT_MAX;
    float NegativeInfinite = -FLT_MAX;

    vec3 left = vec3(-1, 0, 0);
    vec3 right = vec3(1, 0, 0);
    vec3 up = vec3(0, 1, 0);
    vec3 down = vec3(0, -1, 0);
    vec3 forward = vec3(0, 0, 1);
    vec3 back = vec3(0, 0, -1);

    float Min(float a, float b) { return (a < b) ? a : b; }
    float Max(float a, float b) { return (a > b) ? a : b; }
    float Clamp(float t, float a, float b) { return Min(b, Max(a, t)); }
    float Lerp(float s, float e, float t) { return s + (e - s) * t; }
    float InverseLerp(float s, float e, float t) { return (t - s) / (e - s); }
    float LerpAngle(float s, float e, float t)
    {
        float max_angle = PI * 2;
        float difference = fmod(e - s, max_angle);
        return s + (fmod(2 * difference, max_angle) - difference) * t;
    }
    double Abs(double a) { return abs(a); }
    float Abs(float a) { return abs(a); }
    int Abs(int a) { return abs(a); }
    float Sqrt(float a) { return sqrtf(a); }
    float Round(float a) { return round(a); }
    int RoundToInt(float a) { return (int)round(a); }
    float Ceil(float a) { return ceil(a); }
    int CeilToInt(float a) { return (int)ceil(a); }
    float Floor(float a) { return floor(a); }
    int FloorToInt(float a) { return (int)floor(a); }

    float Sin(float a) { return sinf(a); }
    float Cos(float a) { return cosf(a); }
    float Tan(float a) { return tanf(a); }
    float Asin(float a) { return asinf(a); }
    float Acos(float a) { return acosf(a); }
    float Atan(float a) { return atanf(a); }
    float Atan2(float a, float b) { return atan2f(a, b); }

    float Log(float a) { return log(a); }
    float Log10(float a) { return log10(a); }
    float Pow(float a, float b) { return pow(a, b); }
    float Exp(float a) { return exp(a); }

};