#pragma once
#include "Transformer.h"
#include <vector>
class DrawingManager {
public:
    std::vector<Triangle> triangles;

    void addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }

    void drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) const {
        for (const auto& triangle : triangles) {
            // 投影三角形的每个顶点到2D坐标
            Vertex p1 = Transformer::project(triangle.v0, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
            Vertex p2 = Transformer::project(triangle.v1, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
            Vertex p3 = Transformer::project(triangle.v2, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);

            LineDrawer::drawLine(hdc, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), RGB(255, 0, 0));
            LineDrawer::drawLine(hdc, static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), RGB(255, 0, 0));
            LineDrawer::drawLine(hdc, static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p1.x), static_cast<int>(p1.y), RGB(255, 0, 0));
        }
    }
};