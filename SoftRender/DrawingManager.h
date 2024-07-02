#pragma once
#include <vector>
#include <windows.h>
#include "Triangle.h"
class DrawingManager {
public:
    std::vector<Triangle> triangles;

    void addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }

    void drawAll(HDC hdc) const {
        for (const auto& triangle : triangles) {
            triangle.draw(hdc, RGB(255, 0, 0));
        }
    }
};