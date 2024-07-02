#include "Matrix.h"
#include <cmath>
#include <algorithm>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


Matrix::Matrix() {
    std::fill(&m[0][0], &m[0][0] + sizeof(m) / sizeof(float), 0);
}

Vector Matrix::operator*(const Vector& v) const {
    return Vector(
        m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0],
        m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1],
        m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]
    );
}

Matrix Matrix::operator*(const Matrix& mat) const {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * mat.m[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::Identity() {
    Matrix mat;
    for (int i = 0; i < 4; ++i) {
        mat.m[i][i] = 1;
    }
    return mat;
}

Matrix Matrix::Translate(float tx, float ty, float tz) {
    Matrix mat = Identity();
    mat.m[3][0] = tx;
    mat.m[3][1] = ty;
    mat.m[3][2] = tz;
    return mat;
}

Matrix Matrix::Scale(float sx, float sy, float sz) {
    Matrix mat = Identity();
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    return mat;
}

Matrix Matrix::RotateX(float angle) {
    Matrix mat = Identity();
    float rad = angle * M_PI / 180;
    mat.m[1][1] = cos(rad);
    mat.m[2][1] = -sin(rad);
    mat.m[1][2] = sin(rad);
    mat.m[2][2] = cos(rad);
    return mat;
}

Matrix Matrix::RotateY(float angle) {
    Matrix mat = Identity();
    float rad = angle * M_PI / 180;
    mat.m[0][0] = cos(rad);
    mat.m[2][0] = sin(rad);
    mat.m[0][2] = -sin(rad);
    mat.m[2][2] = cos(rad);
    return mat;
}

Matrix Matrix::RotateZ(float angle) {
    Matrix mat = Identity();
    float rad = angle * M_PI / 180;
    mat.m[0][0] = cos(rad);
    mat.m[1][0] = -sin(rad);
    mat.m[0][1] = sin(rad);
    mat.m[1][1] = cos(rad);
    return mat;
}

Matrix Matrix::Perspective(float fov, float aspect, float near, float far) {
    Matrix mat;
    float tanHalfFov = tan(fov / 2);

    mat.m[0][0] = 1 / (aspect * tanHalfFov);
    mat.m[1][1] = 1 / tanHalfFov;
    mat.m[2][2] = -(far + near) / (far - near);
    mat.m[3][2] = -1;
    mat.m[2][3] = -(2 * far * near) / (far - near);

    return mat;
}