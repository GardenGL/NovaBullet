
#include "Matrix4x4.hpp"
namespace Math
{
    mat4x4::mat4x4()
    {
        m[0] = 1.0f;
        m[4] = 0.0f;
        m[8] = 0.0f;
        m[12] = 0.0f;
        m[1] = 0.0f;
        m[5] = 1.0f;
        m[9] = 0.0f;
        m[13] = 0.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        m[10] = 1.0f;
        m[14] = 0.0f;
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = 1.0f;
    }

    mat4x4::mat4x4(float *fv) : xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
                                yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
                                zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
                                tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}

    mat4x4::mat4x4(double *fv) : xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
                                yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
                                zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
                                tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}

    mat4x4::~mat4x4()
    {
    }

    mat4x4::mat4x4(const mat4x4 &Matrix)
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat4x4::mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
    {
        m[0] = col1.x;
        m[4] = col2.x;
        m[8] = col3.x;
        m[12] = col4.x;
        m[1] = col1.y;
        m[5] = col2.y;
        m[9] = col3.y;
        m[13] = col4.y;
        m[2] = col1.z;
        m[6] = col2.z;
        m[10] = col3.z;
        m[14] = col4.z;
        m[3] = col1.w;
        m[7] = col2.w;
        m[11] = col3.w;
        m[15] = col4.w;
    }

    mat4x4::mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4)
    {
        m[0] = c1r1;
        m[4] = c2r1;
        m[8] = c3r1;
        m[12] = c4r1;
        m[1] = c1r2;
        m[5] = c2r2;
        m[9] = c3r2;
        m[13] = c4r2;
        m[2] = c1r3;
        m[6] = c2r3;
        m[10] = c3r3;
        m[14] = c4r3;
        m[3] = c1r4;
        m[7] = c2r4;
        m[11] = c3r4;
        m[15] = c4r4;
    }

    mat4x4::mat4x4(const mat2x2 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[4] = Matrix.m[2];
        m[8] = 0.0f;
        m[12] = 0.0f;
        m[1] = Matrix.m[1];
        m[5] = Matrix.m[3];
        m[9] = 0.0f;
        m[13] = 0.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        m[10] = 1.0f;
        m[14] = 0.0f;
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = 1.0f;
    }

    mat4x4::mat4x4(const mat3x3 &Matrix)
    {
        m[0] = Matrix.m[0];
        m[4] = Matrix.m[3];
        m[8] = Matrix.m[6];
        m[12] = 0.0f;
        m[1] = Matrix.m[1];
        m[5] = Matrix.m[4];
        m[9] = Matrix.m[7];
        m[13] = 0.0f;
        m[2] = Matrix.m[2];
        m[6] = Matrix.m[5];
        m[10] = Matrix.m[8];
        m[14] = 0.0f;
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = 1.0f;
    }

    mat4x4 &mat4x4::operator=(const mat4x4 &Matrix)
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float &mat4x4::operator[](int i)
    {
        return m[i];
    }

    float *mat4x4::operator&()
    {
        return (float *)this;
    }

    mat4x4 operator*(const mat4x4 &Matrix1, const mat4x4 &Matrix2)
    {
        mat4x4 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[4] * Matrix2.m[1] + Matrix1.m[8] * Matrix2.m[2] + Matrix1.m[12] * Matrix2.m[3];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[5] * Matrix2.m[1] + Matrix1.m[9] * Matrix2.m[2] + Matrix1.m[13] * Matrix2.m[3];
        Matrix3.m[2] = Matrix1.m[2] * Matrix2.m[0] + Matrix1.m[6] * Matrix2.m[1] + Matrix1.m[10] * Matrix2.m[2] + Matrix1.m[14] * Matrix2.m[3];
        Matrix3.m[3] = Matrix1.m[3] * Matrix2.m[0] + Matrix1.m[7] * Matrix2.m[1] + Matrix1.m[11] * Matrix2.m[2] + Matrix1.m[15] * Matrix2.m[3];
        Matrix3.m[4] = Matrix1.m[0] * Matrix2.m[4] + Matrix1.m[4] * Matrix2.m[5] + Matrix1.m[8] * Matrix2.m[6] + Matrix1.m[12] * Matrix2.m[7];
        Matrix3.m[5] = Matrix1.m[1] * Matrix2.m[4] + Matrix1.m[5] * Matrix2.m[5] + Matrix1.m[9] * Matrix2.m[6] + Matrix1.m[13] * Matrix2.m[7];
        Matrix3.m[6] = Matrix1.m[2] * Matrix2.m[4] + Matrix1.m[6] * Matrix2.m[5] + Matrix1.m[10] * Matrix2.m[6] + Matrix1.m[14] * Matrix2.m[7];
        Matrix3.m[7] = Matrix1.m[3] * Matrix2.m[4] + Matrix1.m[7] * Matrix2.m[5] + Matrix1.m[11] * Matrix2.m[6] + Matrix1.m[15] * Matrix2.m[7];
        Matrix3.m[8] = Matrix1.m[0] * Matrix2.m[8] + Matrix1.m[4] * Matrix2.m[9] + Matrix1.m[8] * Matrix2.m[10] + Matrix1.m[12] * Matrix2.m[11];
        Matrix3.m[9] = Matrix1.m[1] * Matrix2.m[8] + Matrix1.m[5] * Matrix2.m[9] + Matrix1.m[9] * Matrix2.m[10] + Matrix1.m[13] * Matrix2.m[11];
        Matrix3.m[10] = Matrix1.m[2] * Matrix2.m[8] + Matrix1.m[6] * Matrix2.m[9] + Matrix1.m[10] * Matrix2.m[10] + Matrix1.m[14] * Matrix2.m[11];
        Matrix3.m[11] = Matrix1.m[3] * Matrix2.m[8] + Matrix1.m[7] * Matrix2.m[9] + Matrix1.m[11] * Matrix2.m[10] + Matrix1.m[15] * Matrix2.m[11];
        Matrix3.m[12] = Matrix1.m[0] * Matrix2.m[12] + Matrix1.m[4] * Matrix2.m[13] + Matrix1.m[8] * Matrix2.m[14] + Matrix1.m[12] * Matrix2.m[15];
        Matrix3.m[13] = Matrix1.m[1] * Matrix2.m[12] + Matrix1.m[5] * Matrix2.m[13] + Matrix1.m[9] * Matrix2.m[14] + Matrix1.m[13] * Matrix2.m[15];
        Matrix3.m[14] = Matrix1.m[2] * Matrix2.m[12] + Matrix1.m[6] * Matrix2.m[13] + Matrix1.m[10] * Matrix2.m[14] + Matrix1.m[14] * Matrix2.m[15];
        Matrix3.m[15] = Matrix1.m[3] * Matrix2.m[12] + Matrix1.m[7] * Matrix2.m[13] + Matrix1.m[11] * Matrix2.m[14] + Matrix1.m[15] * Matrix2.m[15];

        return Matrix3;
    }

    vec4 operator*(const mat4x4 &Matrix, const vec4 &u)
    {
        vec4 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[4] * u.y + Matrix.m[8] * u.z + Matrix.m[12] * u.w;
        v.y = Matrix.m[1] * u.x + Matrix.m[5] * u.y + Matrix.m[9] * u.z + Matrix.m[13] * u.w;
        v.z = Matrix.m[2] * u.x + Matrix.m[6] * u.y + Matrix.m[10] * u.z + Matrix.m[14] * u.w;
        v.w = Matrix.m[3] * u.x + Matrix.m[7] * u.y + Matrix.m[11] * u.z + Matrix.m[15] * u.w;

        return v;
    }

    // ----------------------------------------------------------------------------------------------------------------------------

    mat4x4 BiasMatrix = mat4x4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
    mat4x4 BiasMatrixInverse = mat4x4(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f);

    // ----------------------------------------------------------------------------------------------------------------------------
    //
    // 0 4  8 12 | + - + -
    // 1 5  9 13 | - + - +
    // 2 6 10 14 | + - + -
    // 3 7 11 15 | - + - +
    //
    // ----------------------------------------------------------------------------------------------------------------------------

    float det3x3sub(const float *m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
    {
        float det = 0.0f;

        det += m[i0] * det2x2sub(m, i4, i5, i7, i8);
        det -= m[i3] * det2x2sub(m, i1, i2, i7, i8);
        det += m[i6] * det2x2sub(m, i1, i2, i4, i5);

        return det;
    }

    mat4x4 Inverse(const mat4x4 &Matrix)
    {
        const float *m = Matrix.m;

        float det = 0.0f;

        det += m[0] * det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15);
        det -= m[4] * det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15);
        det += m[8] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15);
        det -= m[12] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11);

        mat4x4 inverse;

        inverse.m[0] = det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15) / det;
        inverse.m[1] = -det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15) / det;
        inverse.m[2] = det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15) / det;
        inverse.m[3] = -det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11) / det;
        inverse.m[4] = -det3x3sub(m, 4, 6, 7, 8, 10, 11, 12, 14, 15) / det;
        inverse.m[5] = det3x3sub(m, 0, 2, 3, 8, 10, 11, 12, 14, 15) / det;
        inverse.m[6] = -det3x3sub(m, 0, 2, 3, 4, 6, 7, 12, 14, 15) / det;
        inverse.m[7] = det3x3sub(m, 0, 2, 3, 4, 6, 7, 8, 10, 11) / det;
        inverse.m[8] = det3x3sub(m, 4, 5, 7, 8, 9, 11, 12, 13, 15) / det;
        inverse.m[9] = -det3x3sub(m, 0, 1, 3, 8, 9, 11, 12, 13, 15) / det;
        inverse.m[10] = det3x3sub(m, 0, 1, 3, 4, 5, 7, 12, 13, 15) / det;
        inverse.m[11] = -det3x3sub(m, 0, 1, 3, 4, 5, 7, 8, 9, 11) / det;
        inverse.m[12] = -det3x3sub(m, 4, 5, 6, 8, 9, 10, 12, 13, 14) / det;
        inverse.m[13] = det3x3sub(m, 0, 1, 2, 8, 9, 10, 12, 13, 14) / det;
        inverse.m[14] = -det3x3sub(m, 0, 1, 2, 4, 5, 6, 12, 13, 14) / det;
        inverse.m[15] = det3x3sub(m, 0, 1, 2, 4, 5, 6, 8, 9, 10) / det;

        return inverse;
    }

    mat4x4 Look(const vec3 &eye, const vec3 &center, const vec3 &up)
    {
        vec3 c = Normalize(eye - center);
        vec3 a = Normalize(Cross(up, c));
        vec3 b = Cross(c, a);

        mat4x4 view;

        view.m[0] = a.x;
        view.m[1] = b.x;
        view.m[2] = c.x;
        view.m[4] = a.y;
        view.m[5] = b.y;
        view.m[6] = c.y;
        view.m[8] = a.z;
        view.m[9] = b.z;
        view.m[10] = c.z;
        view.m[12] = -Dot(a, eye);
        view.m[13] = -Dot(b, eye);
        view.m[14] = -Dot(c, eye);

        return view;
    }

    mat4x4 Ortho(float left, float right, float bottom, float top, float n, float f)
    {
        mat4x4 ortho;

        ortho.m[0] = 2.0f / (right - left);
        ortho.m[5] = 2.0f / (top - bottom);
        ortho.m[10] = -2.0f / (f - n);
        ortho.m[12] = -(right + left) / (right - left);
        ortho.m[13] = -(top + bottom) / (top - bottom);
        ortho.m[14] = -(f + n) / (f - n);

        return ortho;
    }

    mat4x4 Perspective(float fovy, float aspect, float n, float f)
    {
        mat4x4 perspective;

        float coty = 1.0f / tan(fovy * (float)M_PI / 360.0f);

        perspective.m[0] = coty / aspect;
        perspective.m[5] = coty;
        perspective.m[10] = (n + f) / (n - f);
        perspective.m[11] = -1.0f;
        perspective.m[14] = 2.0f * n * f / (n - f);
        perspective.m[15] = 0.0f;

        return perspective;
    }

    mat4x4 Transpose(const mat4x4 &Matrix)
    {
        /*mat4x4 Transpose;

        Transpose.m[0] = Matrix.m[0];
        Transpose.m[1] = Matrix.m[4];
        Transpose.m[2] = Matrix.m[8];
        Transpose.m[3] = Matrix.m[12];
        Transpose.m[4] = Matrix.m[1];
        Transpose.m[5] = Matrix.m[5];
        Transpose.m[6] = Matrix.m[9];
        Transpose.m[7] = Matrix.m[13];
        Transpose.m[8] = Matrix.m[2];
        Transpose.m[9] = Matrix.m[6];
        Transpose.m[10] = Matrix.m[10];
        Transpose.m[11] = Matrix.m[14];
        Transpose.m[12] = Matrix.m[3];
        Transpose.m[13] = Matrix.m[7];
        Transpose.m[14] = Matrix.m[11];
        Transpose.m[15] = Matrix.m[15];*/

        return mat4x4(Matrix.m[0], Matrix.m[4], Matrix.m[8], Matrix.m[12],
                      Matrix.m[1], Matrix.m[5], Matrix.m[9], Matrix.m[13],
                      Matrix.m[2], Matrix.m[6], Matrix.m[10], Matrix.m[14],
                      Matrix.m[3], Matrix.m[7], Matrix.m[11], Matrix.m[15]);
    }

    mat4x4 Rotate(float angle, const vec3 &u)
    {
        mat4x4 rotate;

        angle = angle / 180.0f * (float)M_PI;

        vec3 v = Normalize(u);

        float c = 1.0f - cos(angle), s = sin(angle);

        rotate.m[0] = 1.0f + c * (v.x * v.x - 1.0f);
        rotate.m[1] = c * v.x * v.y + v.z * s;
        rotate.m[2] = c * v.x * v.z - v.y * s;
        rotate.m[4] = c * v.x * v.y - v.z * s;
        rotate.m[5] = 1.0f + c * (v.y * v.y - 1.0f);
        rotate.m[6] = c * v.y * v.z + v.x * s;
        rotate.m[8] = c * v.x * v.z + v.y * s;
        rotate.m[9] = c * v.y * v.z - v.x * s;
        rotate.m[10] = 1.0f + c * (v.z * v.z - 1.0f);

        return rotate;
    }

    mat4x4 Scale(vec3 vec)
    {
        mat4x4 scale;

        scale.m[0] = vec.x;
        scale.m[5] = vec.y;
        scale.m[10] = vec.z;

        return scale;
    }

    mat4x4 Translate(vec3 vec)
    {
        mat4x4 translate;

        translate.m[12] = vec.x;
        translate.m[13] = vec.y;
        translate.m[14] = vec.z;

        return translate;
    }

    mat4x4 TransformToMat4x4(vec3 position, vec3 scale)
    {
        mat4x4 transformMatrix;
        transformMatrix.m[0] = scale.x;
        transformMatrix.m[5] = scale.y;
        transformMatrix.m[10] = scale.z;

        transformMatrix.m[12] = position.x;
        transformMatrix.m[13] = position.y;
        transformMatrix.m[14] = position.z;

        return transformMatrix;
    }
    mat4x4 TransformToMat4x4(vec3 position, quat rotation)
    {
        return TransformToMat4x4(position, rotation, vec3(1.0f));
    }
    mat4x4 TransformToMat4x4(vec3 position, quat rotation, vec3 scale)
    {
        // First, extract the rotation basis of the transform

        vec3 x = rotation * Math::right;
        vec3 y = rotation * Math::up;
        vec3 z = rotation * Math::forward;

        // Next, scale the basis vectors
        x = x * scale.x;
        y = y * scale.y;
        z = z * scale.z;

        // Extract the position of the transform
        vec3 p = position;

        // Create matrix
        return mat4x4(
            x.x, x.y, x.z, 0, // X basis (& Scale)
            y.x, y.y, y.z, 0, // Y basis (& scale)
            z.x, z.y, z.z, 0, // Z basis (& scale)
            p.x, p.y, p.z, 1  // Position
        );
    }

};