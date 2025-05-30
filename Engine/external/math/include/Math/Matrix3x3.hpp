#ifndef MATRIX3X3_HPP
#define MATRIX3X3_HPP

#include "glmath.hpp"
namespace Math
{
    class mat3x3
    {
    public:
        union
        {
            float m[9];

            struct
            {
                //            row 1     row 2     row 3
                /* column 1 */ float xx; // 0
                float xy;                // 1
                float xz;                // 2
                /* column 2 */ float yx; // 3
                float yy;                // 4
                float yz;                // 5
                /* column 3 */ float zx; // 6
                float zy;                // 7
                float zz;                // 8
            };
            struct
            {
                float v[3][3];
            };
        };

        mat3x3();
        ~mat3x3();
        mat3x3(const mat3x3 &Matrix);
        mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3);
        mat3x3(float c1r1, float c1r2, float c1r3, float c2r1, float c2r2, float c2r3, float c3r1, float c3r2, float c3r3);
        explicit mat3x3(const mat2x2 &Matrix);
        explicit mat3x3(const mat4x4 &Matrix);
        mat3x3 &operator=(const mat3x3 &Matrix);
        mat3x3 &operator=(const mat4x4 &Matrix);
        float &operator[](int i);
        float *operator&();
        friend mat3x3 operator*(const mat3x3 &Matrix1, const mat3x3 &Matrix2);
        friend vec3 operator*(const mat3x3 &Matrix, const vec3 &u);
    };

    mat3x3 Inverse(const mat3x3 &Matrix);
    mat3x3 Transpose(const mat3x3 &Matrix);

    inline float det2x2sub(const float *m, int i0, int i1, int i2, int i3)
    {
        return m[i0] * m[i3] - m[i2] * m[i1];
    }
};

#endif