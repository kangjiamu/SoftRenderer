#pragma once

#include "Vector.h"
#include "Color.h"

struct DirectionalLight
{
    Vector direction;
    Color color;

    DirectionalLight(const Vector& dir, const Color& col)
        : direction(dir), color(col) {}
};

struct AmbientLight
{
    Color color;

    AmbientLight(const Color& col)
        : color(col) {}
};
