#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include "glmath.hpp"
#include "Vector3.hpp"
namespace Math
{
    class quat
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
                float v[4];
            };
        };
        quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
   
        ~quat() {}

        quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        quat(const quat &u) : x(u.x), y(u.y), z(u.z), w(u.w) {}

        friend quat operator/(const quat &q, float rhs)
        {
            quat result;
            result.x = q.x / rhs;
            result.y = q.y / rhs;
            result.z = q.z / rhs;
            result.w = q.w / rhs;
            return result;
        }

        friend quat operator*(const quat &Q1, const quat &Q2)
        {
            return quat(
                Q2.x * Q1.w + Q2.y * Q1.z - Q2.z * Q1.y + Q2.w * Q1.x,
                -Q2.x * Q1.z + Q2.y * Q1.w + Q2.z * Q1.x + Q2.w * Q1.y,
                Q2.x * Q1.y - Q2.y * Q1.x + Q2.z * Q1.w + Q2.w * Q1.z,
                -Q2.x * Q1.x - Q2.y * Q1.y - Q2.z * Q1.z + Q2.w * Q1.w);
        }

        friend quat operator+(const quat &a, const quat &b)
        {
            return quat(
                a.x + b.x,
                a.y + b.y,
                a.z + b.z,
                a.w + b.w);
        }

        friend quat operator-(const quat &a, const quat &b)
        {
            return quat(
                a.x - b.x,
                a.y - b.y,
                a.z - b.z,
                a.w - b.w);
        }

        friend quat operator*(const quat &a, float b) { return quat(a.x * b, a.y * b, a.z * b, a.w * b); }

        friend quat operator-(const quat &q) { return quat(-q.x, -q.y, -q.z, -q.w); }

        friend bool operator==(const quat &left, const quat &right) { return (fabsf(left.x - right.x) <= Epsilon && fabsf(left.y - right.y) <= Epsilon && fabsf(left.z - right.z) <= Epsilon && fabsf(left.w - left.w) <= Epsilon); }

        friend bool operator!=(const quat &a, const quat &b) { return !(a == b); }
    };

    float Dot(const quat &u, const quat &v);
    float SqrtMagnitude(const quat &u);
    float Magnitude(const quat &u);

    quat Euler(float pitch, float yaw, float roll);

    quat Quaternion(float Pitch, float Yaw, float Roll);
    quat AngleAxis(float angle, const vec3 &axis);
    quat FromTo(const vec3 &from, const vec3 &to);
    vec3 GetAxis(const quat &quat);
    float GetAngle(const quat &quat);

    quat Normalize(const quat &q);
    quat Conjugate(const quat &q);
    quat Inverse(const quat &q);
    bool SameOrientation(const quat &left, const quat &right);

    quat Mix(const quat &from, const quat &to, float t);
    quat Nlerp(const quat &from, const quat &to, float t);
    quat operator^(const quat &q, float f);
    quat Slerp(const quat &start, const quat &end, float t);

    quat LookRotation(const vec3 &direcion, const vec3 &up);
    mat4x4 QuatToMat4(const quat &q);
    quat Mat4ToQuat(const mat4x4 &m);
    quat QuaternionTransform(quat q, mat4x4 mat);

    vec3 operator*(const quat &q, const vec3 &v);

    vec3 GetVector(const quat &q);
    float GetScalar(const quat &q);

};
#endif