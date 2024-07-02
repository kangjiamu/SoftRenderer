#include "Vector.h"
#include <iostream>

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
}

float Vector::DotProduct(const Vector& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::CrossProduct(const Vector& v) const {
    return Vector(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

void Vector::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")";
}