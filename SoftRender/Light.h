#pragma once

#include "Vector.h"
#include "Color.h"

struct DirectionalLight
{
    Vector direction;
    Color color;
    DirectionalLight() = default; // 默认构造函数
    DirectionalLight(const Vector& dir, const Color& col)
        : direction(dir), color(col) {}
};

struct AmbientLight
{
    Color color;
    AmbientLight() = default; // 默认构造函数

    AmbientLight(const Color& col)
        : color(col) {}
};
