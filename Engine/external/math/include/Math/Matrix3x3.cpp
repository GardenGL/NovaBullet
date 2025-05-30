#include "Matrix3x3.hpp"

namespace Math
{
    mat3x3::mat3x3()
    {
        m[0] = 1.0f;
        m[3] = 0.0f;
        m[6] = 0.0f;
        m[1] = 0.0f;
        m[4] = 1.0f;
        m[7] = 0.0f;
        m[2] = 0.0f;
        m[5] = 0.0f;
        m[8] = 1.0f;
    }

    mat3x3::~mat3x3()
    {
    }

    mat3x3::mat3x3(const mat3x3 &Matrix)
    {
        for (int i = 0; i < 9; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat3x3::mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3)
    {
        m[0] = col1.x;
        m[3] = col2.x;
        m[6] = col3.x;
        m[1] = col1.y;
        m[4] = col2.y;
        m[7] = col3.y;
        m[2] = col1.z;
        m[5] = col2.z;
        m[8] = col3.z;
    }

    mat3x3::mat3x3(float c1r1, float c1r2, float c1r3, float c2r1, float c2r2, float c2r3, float c3r1, float c3r2, float c3r3)
    {
        m[0] = c1r1;
        m[3] = c2r1;
        m[6] = c3r1;
        m[1] = c1r2;
        m[4] = c2r2;
        m[7] = c3r2;
        m[2] = c1r3;
        m[5] = c2r3;
        m[8] = c3r3;
    }

    mat3x3::mat3x3(const mat2x2 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[3] = Matrix.m[2];
        m[6] = 0.0f;
        m[1] = Matrix.m[1];
        m[4] = Matrix.m[3];
        m[7] = 0.0f;
        m[2] = 0.0f;
        m[5] = 0.0f;
        m[8] = 1.0f;
    }

    mat3x3::mat3x3(const mat4x4 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[3] = Matrix.m[4];
        m[6] = Matrix.m[8];
        m[1] = Matrix.m[1];
        m[4] = Matrix.m[5];
        m[7] = Matrix.m[9];
        m[2] = Matrix.m[2];
        m[5] = Matrix.m[6];
        m[8] = Matrix.m[10];
    }

    mat3x3 &mat3x3::operator=(const mat4x4 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[3] = Matrix.m[4];
        m[6] = Matrix.m[8];
        m[1] = Matrix.m[1];
        m[4] = Matrix.m[5];
        m[7] = Matrix.m[9];
        m[2] = Matrix.m[2];
        m[5] = Matrix.m[6];
        m[8] = Matrix.m[10];
        return *this;
    }

    mat3x3 &mat3x3::operator=(const mat3x3 &Matrix)
    {
        for (int i = 0; i < 9; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float &mat3x3::operator[](int i)
    {
        return m[i];
    }

    float *mat3x3::operator&()
    {
        return (float *)this;
    }

    mat3x3 operator*(const mat3x3 &Matrix1, const mat3x3 &Matrix2)
    {
        mat3x3 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[3] * Matrix2.m[1] + Matrix1.m[6] * Matrix2.m[2];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[4] * Matrix2.m[1] + Matrix1.m[7] * Matrix2.m[2];
        Matrix3.m[2] = Matrix1.m[2] * Matrix2.m[0] + Matrix1.m[5] * Matrix2.m[1] + Matrix1.m[8] * Matrix2.m[2];
        Matrix3.m[3] = Matrix1.m[0] * Matrix2.m[3] + Matrix1.m[3] * Matrix2.m[4] + Matrix1.m[6] * Matrix2.m[5];
        Matrix3.m[4] = Matrix1.m[1] * Matrix2.m[3] + Matrix1.m[4] * Matrix2.m[4] + Matrix1.m[7] * Matrix2.m[5];
        Matrix3.m[5] = Matrix1.m[2] * Matrix2.m[3] + Matrix1.m[5] * Matrix2.m[4] + Matrix1.m[8] * Matrix2.m[5];
        Matrix3.m[6] = Matrix1.m[0] * Matrix2.m[6] + Matrix1.m[3] * Matrix2.m[7] + Matrix1.m[6] * Matrix2.m[8];
        Matrix3.m[7] = Matrix1.m[1] * Matrix2.m[6] + Matrix1.m[4] * Matrix2.m[7] + Matrix1.m[7] * Matrix2.m[8];
        Matrix3.m[8] = Matrix1.m[2] * Matrix2.m[6] + Matrix1.m[5] * Matrix2.m[7] + Matrix1.m[8] * Matrix2.m[8];

        return Matrix3;
    }

    vec3 operator*(const mat3x3 &Matrix, const vec3 &u)
    {
        vec3 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[3] * u.y + Matrix.m[6] * u.z;
        v.y = Matrix.m[1] * u.x + Matrix.m[4] * u.y + Matrix.m[7] * u.z;
        v.z = Matrix.m[2] * u.x + Matrix.m[5] * u.y + Matrix.m[8] * u.z;

        return v;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    //
    // 0 3 6 | + - +
    // 1 4 7 | - + -
    // 2 5 8 | + - +
    //
    // ----------------------------------------------------------------------------------------------------------------------------

    mat3x3 Inverse(const mat3x3 &Matrix)
    {
        const float *m = Matrix.m;

        float det = 0.0f;

        det += m[0] * det2x2sub(m, 4, 5, 7, 8);
        det -= m[3] * det2x2sub(m, 1, 2, 7, 8);
        det += m[6] * det2x2sub(m, 1, 2, 4, 5);

        mat3x3 inverse;

        inverse.m[0] = det2x2sub(m, 4, 5, 7, 8) / det;
        inverse.m[1] = -det2x2sub(m, 1, 2, 7, 8) / det;
        inverse.m[2] = det2x2sub(m, 1, 2, 4, 5) / det;
        inverse.m[3] = -det2x2sub(m, 3, 5, 6, 8) / det;
        inverse.m[4] = det2x2sub(m, 0, 2, 6, 8) / det;
        inverse.m[5] = -det2x2sub(m, 0, 2, 3, 5) / det;
        inverse.m[6] = det2x2sub(m, 3, 4, 6, 7) / det;
        inverse.m[7] = -det2x2sub(m, 0, 1, 6, 7) / det;
        inverse.m[8] = det2x2sub(m, 0, 1, 3, 4) / det;

        return inverse;
    }

    mat3x3 Transpose(const mat3x3 &Matrix)
    {
        mat3x3 transpose;

        transpose.m[0] = Matrix.m[0];
        transpose.m[1] = Matrix.m[3];
        transpose.m[2] = Matrix.m[6];
        transpose.m[3] = Matrix.m[1];
        transpose.m[4] = Matrix.m[4];
        transpose.m[5] = Matrix.m[7];
        transpose.m[6] = Matrix.m[2];
        transpose.m[7] = Matrix.m[5];
        transpose.m[8] = Matrix.m[8];

        return transpose;
    }

};
