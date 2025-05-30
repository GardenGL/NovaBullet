#include "Quaternion.hpp"
namespace Math
{
   
    vec3 operator*(const quat &q, const vec3 &v)
    {
        vec3 vector = GetVector(q);
        float scalar = GetScalar(q);
        return vector * 2.0f * Dot(vector, v) +
               v * (scalar * scalar - Dot(vector, vector)) +
               Cross(vector, v) * 2.0f * scalar;
    }

    float Dot(const quat &u, const quat &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
    }
    float SqrtMagnitude(const quat &u)
    {
        return Math::Sqrt(Magnitude(u));
    }
    float Magnitude(const quat &u)
    {
        return Dot(u, u);
    }

    quat Euler(float pitch, float yaw, float roll)
    {
        quat q;
        q = q * AngleAxis(pitch * Math::Deg2Rad, Math::right);
        q = q * AngleAxis(yaw * Math::Deg2Rad, Math::up);
        q = q * AngleAxis(roll * Math::Deg2Rad, q * Math::forward);

        return Normalize(q);
    }

    quat Quaternion(float Pitch, float Yaw, float Roll)
    {
        quat result;

        float Pi = 4 * atan(1);

        // Set the values, which came in degrees, to radians for C++ trig functions
        float rYaw = Yaw * Pi / 180;
        float rPitch = Pitch * Pi / 180;
        float rRoll = Roll * Pi / 180;

        // Components
        float C1 = cos(rYaw / 2);
        float C2 = cos(rPitch / 2);
        float C3 = cos(rRoll / 2);
        float S1 = sin(rYaw / 2);
        float S2 = sin(rPitch / 2);
        float S3 = sin(rRoll / 2);

        // Create the final values
        result.w = ((C1 * C2 * C3) - (S1 * S2 * S3));
        result.x = (S1 * S2 * C3) + (C1 * C2 * S3);
        result.y = (S1 * C2 * C3) + (C1 * S2 * S3);
        result.z = (C1 * S2 * C3) - (S1 * C2 * S3);

        return result;
    }

    quat AngleAxis(float angle, const vec3 &axis)
    {
        vec3 norm = Normalize(axis);
        float s = sinf(angle * 0.5f);

        return quat(
            norm.x * s,
            norm.y * s,
            norm.z * s,
            cosf(angle * 0.5f));
    }

    quat FromTo(const vec3 &from, const vec3 &to)
    {
        vec3 f = Normalize(from);
        vec3 t = Normalize(to);

        if (f == t)
        {
            return quat();
        }
        else if (f == t * -1.0f)
        {
            vec3 ortho = vec3(1, 0, 0);
            if (fabsf(f.y) < fabsf(f.x))
            {
                ortho = vec3(0, 1, 0);
            }
            if (fabsf(f.z) < fabs(f.y) && fabs(f.z) < fabsf(f.x))
            {
                ortho = vec3(0, 0, 1);
            }

            vec3 axis = Normalize(Cross(f, ortho));
            return quat(axis.x, axis.y, axis.z, 0);
        }

        vec3 half = Normalize(f + t);
        vec3 axis = Cross(f, half);

        return quat(
            axis.x,
            axis.y,
            axis.z,
            Dot(f, half));
    }

    vec3 GetAxis(const quat &quat)
    {
        return Normalize(vec3(quat.x, quat.y, quat.z));
    }

    float GetAngle(const quat &quat)
    {
        return 2.0f * acosf(quat.w);
    }

    bool sameOrientation(const quat &left, const quat &right)
    {
        return (fabsf(left.x - right.x) <= Epsilon && fabsf(left.y - right.y) <= Epsilon && fabsf(left.z - right.z) <= Epsilon && fabsf(left.w - left.w) <= Epsilon) || (fabsf(left.x + right.x) <= Epsilon && fabsf(left.y + right.y) <= Epsilon && fabsf(left.z + right.z) <= Epsilon && fabsf(left.w + left.w) <= Epsilon);
    }

    quat Normalize(const quat &q)
    {
        float sum =
            q.x * q.x + q.y * q.y +
            q.z * q.z + q.w * q.w;
        // NB: floats have min 6 digits of precision
        const float thresh = 0.0001f;
        if (sum < Epsilon)
        {
            return q;
        }
        float mag = sqrt(sum);
        return q / mag;
    }

    quat Conjugate(const quat &q)
    {
        return quat(
            -q.x,
            -q.y,
            -q.z,
            q.w);
    }

    quat Inverse(const quat &q)
    {
        float lenSq = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
        if (lenSq < Epsilon)
        {
            return quat();
        }
        float recip = 1.0f / lenSq;

        // conjugate / norm
        return quat(
            -q.x * recip,
            -q.y * recip,
            -q.z * recip,
            q.w * recip);
    }

    quat Mix(const quat &from, const quat &to, float t)
    {
        return from * (1.0f - t) + to * t;
    }

    quat Nlerp(const quat &from, const quat &to, float t)
    {
        return Normalize(from + (to - from) * t);
    }

    quat operator^(const quat &q, float f)
    {
        vec3 vector = GetVector(q);
        float scalar = GetScalar(q);
        float angle = 2.0f * acosf(scalar);
        vec3 axis = Normalize(vector);

        float halfCos = cosf(f * angle * 0.5f);
        float halfSin = sinf(f * angle * 0.5f);

        return quat(
            axis.x * halfSin,
            axis.y * halfSin,
            axis.z * halfSin,
            halfCos);
    }

    quat Slerp(const quat &start, const quat &end, float t)
    {
        if (fabsf(Dot(start, end)) > 1.0f - Epsilon)
        {
            return Nlerp(start, end, t);
        }

        return Normalize(((Inverse(start) * end) ^ t) * start);
    }

    quat LookRotation(const vec3 &direcion, const vec3 &up)
    {
        // Find orthonormal basis vectors
        vec3 f = Normalize(direcion);
        vec3 u = Normalize(up);
        vec3 r = Cross(u, f);
        u = Cross(f, r);

        // From world forward to object forward
        quat f2d = FromTo(vec3(0, 0, 1), f);

        // what direction is the new object up?
        vec3 objectUp = f2d * vec3(0, 1, 0);
        // From object up to desired up
        quat u2u = FromTo(objectUp, u);

        // Rotate to forward direction first, then twist to correct up
        quat result = f2d * u2u;
        // Don�t forget to normalize the result
        return Normalize(result);
    }

    mat4x4 QuatToMat4(const quat &q)
    {
        vec3 r = q * vec3(1, 0, 0);
        vec3 u = q * vec3(0, 1, 0);
        vec3 f = q * vec3(0, 0, 1);

        return mat4x4(
            r.x, r.y, r.z, 0,
            u.x, u.y, u.z, 0,
            f.x, f.y, f.z, 0,
            0, 0, 0, 1);
    }

    quat Mat4ToQuat(const mat4x4 &m)
    {

        vec3 up = Normalize(vec3(m.yx, m.yy, m.yz));
        vec3 forward = Normalize(vec3(m.zx, m.zy, m.zz));
        vec3 right = Cross(up, forward);
        up = Cross(forward, right);

        return LookRotation(forward, up);
    }

    quat QuaternionTransform(quat q, mat4x4 mat)
    {
        quat result;

        result.x = mat.xx * q.x + mat.yx * q.y + mat.zx * q.z + mat.tx * q.w;
        result.y = mat.xy * q.x + mat.yy * q.y + mat.zy * q.z + mat.ty * q.w;
        result.z = mat.xz * q.x + mat.yz * q.y + mat.zz * q.z + mat.tz * q.w;
        result.w = mat.xw * q.x + mat.yw * q.y + mat.zw * q.z + mat.tw * q.w;

        return result;
    }

    vec3 GetVector(const quat &q) { return vec3(q.x, q.y, q.z); }
    float GetScalar(const quat &q) { return q.w; }



}