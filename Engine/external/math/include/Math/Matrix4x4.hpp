#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP
#include "glmath.hpp"
#include "Quaternion.hpp"
namespace Math
{
    class mat4x4
    {
    public:
        union
        {

            float m[16];

            struct
            {
                //            row 1     row 2     row 3     row 4
                /* column 1 */ float xx; // 0
                float xy;                // 1
                float xz;                // 2
                float xw;                // 3
                /* column 2 */ float yx; // 4
                float yy;                // 5
                float yz;                // 6
                float yw;                // 7
                /* column 3 */ float zx; // 8
                float zy;                // 9
                float zz;                // 10
                float zw;                // 11
                /* column 4 */ float tx; // 12
                float ty;                // 13
                float tz;                // 14
                float tw;                // 15
            };
            struct
            {
                float c0r0;
                float c0r1;
                float c0r2;
                float c0r3;
                float c1r0;
                float c1r1;
                float c1r2;
                float c1r3;
                float c2r0;
                float c2r1;
                float c2r2;
                float c2r3;
                float c3r0;
                float c3r1;
                float c3r2;
                float c3r3;
            };
            struct
            {
                float r0c0;
                float r1c0;
                float r2c0;
                float r3c0;
                float r0c1;
                float r1c1;
                float r2c1;
                float r3c1;
                float r0c2;
                float r1c2;
                float r2c2;
                float r3c2;
                float r0c3;
                float r1c3;
                float r2c3;
                float r3c3;
            };
            struct
            {
                float v[4][4];
            };
        };
        mat4x4();
        mat4x4(float *fv);
         mat4x4(double *fv);
        ~mat4x4();
        mat4x4(const mat4x4 &Matrix);
        mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4);
        mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4);
        explicit mat4x4(const mat2x2 &Matrix);
        explicit mat4x4(const mat3x3 &Matrix);
        mat4x4 &operator=(const mat4x4 &Matrix);
        float &operator[](int i);
        float *operator&();
        friend mat4x4 operator*(const mat4x4 &Matrix1, const mat4x4 &Matrix2);
        friend vec4 operator*(const mat4x4 &Matrix, const vec4 &u);
    };

    // ----------------------------------------------------------------------------------------------------------------------------

    extern mat4x4 BiasMatrix;
    extern mat4x4 BiasMatrixInverse;

    // ----------------------------------------------------------------------------------------------------------------------------

    mat4x4 Inverse(const mat4x4 &Matrix);
    mat4x4 Look(const vec3 &eye, const vec3 &center, const vec3 &up);
    mat4x4 Ortho(float left, float right, float bottom, float top, float n, float f);
    mat4x4 Perspective(float fovy, float aspect, float n, float f);
    mat4x4 Rotate(float angle, const vec3 &u);
    mat4x4 Scale(vec3 vec);
    mat4x4 Translate(vec3 vec);
    mat4x4 Transpose(const mat4x4 &Matrix);
    mat4x4 TransformToMat4x4(vec3 position, quat rotation, vec3 scale);
    mat4x4 TransformToMat4x4(vec3 position, quat rotation);
    mat4x4 TransformToMat4x4(vec3 position, vec3 scale);

};
#endif