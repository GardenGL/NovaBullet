#ifndef MATRIX2X2_HPP
#define MATRIX2X2_HPP

#include "glmath.hpp"

namespace Math
{
    class mat2x2
    {
    public:
        float m[4];
        mat2x2();
        ~mat2x2();
        mat2x2(const mat2x2 &Matrix);
        mat2x2(const vec2 &col1, const vec2 &col2);
        mat2x2(float c1r1, float c1r2, float c2r1, float c2r2);
        explicit mat2x2(const mat3x3 &Matrix);
        explicit mat2x2(const mat4x4 &Matrix);
        mat2x2 &operator=(const mat2x2 &Matrix);
        float &operator[](int i);
        float *operator&();
        friend mat2x2 operator*(const mat2x2 &Matrix1, const mat2x2 &Matrix2);
        friend vec2 operator*(const mat2x2 &Matrix, const vec2 &u);
    };
    mat2x2 Inverse(const mat2x2 &Matrix);
    mat2x2 Transpose(const mat2x2 &Matrix);

    // ----------------------------------------------------------------------------------------------------------------------------
};
#endif