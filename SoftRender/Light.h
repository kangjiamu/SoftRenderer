#pragma once

#include "Vector.h"
#include "Color.h"

struct DirectionalLight
{
    Vector direction;
    Color color;
    DirectionalLight() = default; // Ĭ�Ϲ��캯��
    DirectionalLight(const Vector& dir, const Color& col)
        : direction(dir), color(col) {}
};

struct AmbientLight
{
    Color color;
    AmbientLight() = default; // Ĭ�Ϲ��캯��

    AmbientLight(const Color& col)
        : color(col) {}
};
