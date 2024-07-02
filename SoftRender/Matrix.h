#pragma once

#include "Vector.h"

class Matrix {
public:
    float m[4][4];

    Matrix();
    Matrix operator*(const Matrix& mat) const;
    Vector operator*(const Vector& v) const;

    static Matrix Identity();
    static Matrix Translate(float tx, float ty, float tz);
    static Matrix Scale(float sx, float sy, float sz);
    static Matrix RotateX(float angle);
    static Matrix RotateY(float angle);
    static Matrix RotateZ(float angle);
    static Matrix Perspective(float fov, float aspect, float near, float far);
};



