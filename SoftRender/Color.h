#pragma once

struct Color
{
    float r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    static Color interpolate(const Color& c1, const Color& c2, float t) {
        return c1 * (1 - t) + c2 * t;
    }
};
