#pragma once

class Vector {
public:
    float x, y, z;

    Vector();
    Vector(float x, float y, float z);

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    float DotProduct(const Vector& v) const;
    Vector CrossProduct(const Vector& v) const;

    void print() const;
};

