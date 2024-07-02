#pragma once

#include "Vertex.h"
#include <Windows.h>
#include "LineDrawer.h"

class Triangle {
public:
    Vertex v0, v1, v2;

    Triangle(Vertex v0, Vertex v1, Vertex v2);

    void draw(HDC hdc, COLORREF color) const {
        /*
        LineDrawer::drawLine(hdc, static_cast<int>(v1.x), static_cast<int>(v1.y), static_cast<int>(v2.x), static_cast<int>(v2.y), color);
        LineDrawer::drawLine(hdc, static_cast<int>(v2.x), static_cast<int>(v2.y), static_cast<int>(v3.x), static_cast<int>(v3.y), color);
        LineDrawer::drawLine(hdc, static_cast<int>(v3.x), static_cast<int>(v3.y), static_cast<int>(v1.x), static_cast<int>(v1.y), color);*/
    }
};

