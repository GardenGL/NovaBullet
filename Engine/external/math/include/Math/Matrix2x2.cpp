#include "Matrix2x2.hpp"

namespace Math
{
    mat2x2::mat2x2()
    {
        m[0] = 1.0f;
        m[2] = 0.0f;
        m[1] = 0.0f;
        m[3] = 1.0f;
    }

    mat2x2::~mat2x2()
    {
    }

    mat2x2::mat2x2(const mat2x2 &Matrix)
    {
        for (int i = 0; i < 4; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat2x2::mat2x2(const vec2 &col1, const vec2 &col2)
    {
        m[0] = col1.x;
        m[2] = col2.x;
        m[1] = col1.y;
        m[3] = col2.y;
    }

    mat2x2::mat2x2(float c1r1, float c1r2, float c2r1, float c2r2)
    {
        m[0] = c1r1;
        m[2] = c2r1;
        m[1] = c1r2;
        m[3] = c2r2;
    }

    mat2x2::mat2x2(const mat3x3 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[2] = Matrix.m[3];
        m[1] = Matrix.m[1];
        m[3] = Matrix.m[4];
    }

    mat2x2::mat2x2(const mat4x4 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[2] = Matrix.m[4];
        m[1] = Matrix.m[1];
        m[3] = Matrix.m[5];
    }

    mat2x2 &mat2x2::operator=(const mat2x2 &Matrix)
    {
        for (int i = 0; i < 4; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float &mat2x2::operator[](int i)
    {
        return m[i];
    }

    float *mat2x2::operator&()
    {
        return (float *)this;
    }

    mat2x2 operator*(const mat2x2 &Matrix1, const mat2x2 &Matrix2)
    {
        mat2x2 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[2] * Matrix2.m[1];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[3] * Matrix2.m[1];
        Matrix3.m[2] = Matrix1.m[0] * Matrix2.m[2] + Matrix1.m[2] * Matrix2.m[3];
        Matrix3.m[3] = Matrix1.m[1] * Matrix2.m[2] + Matrix1.m[3] * Matrix2.m[3];

        return Matrix3;
    }

    vec2 operator*(const mat2x2 &Matrix, const vec2 &u)
    {
        vec2 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[2] * u.y;
        v.y = Matrix.m[1] * u.x + Matrix.m[3] * u.y;

        return v;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    //
    // 0 2
    // 1 3
    //
    // ----------------------------------------------------------------------------------------------------------------------------

    mat2x2 Inverse(const mat2x2 &Matrix)
    {
        const float *m = Matrix.m;

        float det = m[0] * m[3] - m[2] * m[1];

        mat2x2 inverse;

        inverse.m[0] = m[3] / det;
        inverse.m[1] = -m[1] / det;
        inverse.m[2] = -m[2] / det;
        inverse.m[3] = m[0] / det;

        return inverse;
    }

    mat2x2 Transpose(const mat2x2 &Matrix)
    {
        mat2x2 transpose;

        transpose.m[0] = Matrix.m[0];
        transpose.m[1] = Matrix.m[2];
        transpose.m[2] = Matrix.m[1];
        transpose.m[3] = Matrix.m[3];

        return transpose;
    }
};
