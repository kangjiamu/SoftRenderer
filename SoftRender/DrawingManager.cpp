#include "DrawingManager.h"
void DrawingManager::addTriangle(const Triangle& triangle) {
    triangles.push_back(triangle);
}
void DrawingManager::calculateLighting(Vertex& vertex) {
    float NdotL = 0.0f > vertex.normal.DotProduct(directionalLight_.direction) ? 0.0f : vertex.normal.DotProduct(directionalLight_.direction);
    Color diffuse = directionalLight_.color * NdotL;
    vertex.color = vertex.color + ambientLight_.color + diffuse;
}

void DrawingManager::drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) {
  /*  for (auto& vertex : vertices_) {
        calculateLighting(vertex);
    }*/
  
    for (const auto& tri : triangles_) {
        // 投影三角形的每个顶点到2D坐标

        Vertex p1 = Transformer::project(vertices_[std::get<0>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
        Vertex p2 = Transformer::project(vertices_[std::get<1>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
        Vertex p3 = Transformer::project(vertices_[std::get<2>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);

        LineDrawer::drawLine(hdc, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), p1.color, p2.color);
        LineDrawer::drawLine(hdc, static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), p2.color, p3.color);
        LineDrawer::drawLine(hdc, static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p1.x), static_cast<int>(p1.y), p3.color, p1.color);
    } 
     for (const auto& tri : triangles_) {
        Vertex p1 = Transformer::project(vertices_[std::get<0>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
        Vertex p2 = Transformer::project(vertices_[std::get<1>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
        Vertex p3 = Transformer::project(vertices_[std::get<2>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
        drawTriangle(hdc, p1, p2, p3);
    }
}
void DrawingManager::setAmbientLight(const Color& color) {
    ambientLight_.color = color;
}

void DrawingManager::setDirectionalLight(const Vector& direction, const Color& color) {
    directionalLight_.direction = direction.normalize();
    directionalLight_.color = color;
}
void DrawingManager::addTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) {
    int idx = vertices_.size();
    vertices_.emplace_back(v0);
    vertices_.emplace_back(v1);
    vertices_.emplace_back(v2);
    triangles_.emplace_back(idx, idx + 1, idx + 2);
}

void DrawingManager::drawTriangle(HDC hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2) {
    // 获取三角形的边界框
    int minX = static_cast<int>(myMin({ v0.x, v1.x, v2.x }));
    int maxX = static_cast<int>(myMax({ v0.x, v1.x, v2.x }));
    int minY = static_cast<int>(myMin({ v0.y, v1.y, v2.y }));
    int maxY = static_cast<int>(myMax({ v0.y, v1.y, v2.y }));

    // 遍历边界框内的每个像素
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            float w0, w1, w2;
            if (computeBarycentricCoordinates(x, y, v0, v1, v2, w0, w1, w2)) {
                float depth = v0.z * w0 + v1.z * w1 + v2.z * w2;
                //if (depth < depthBuffer_[y * width_ + x]) {
                    depthBuffer_[y * width_ + x] = depth;
                    // 通过重心坐标插值颜色
                    Color color = v0.color * w0 + v1.color * w1 + v2.color * w2;
                    SetPixel(hdc, x, y, color.toCOLORREF());
                //}
            }
        }
    }
}