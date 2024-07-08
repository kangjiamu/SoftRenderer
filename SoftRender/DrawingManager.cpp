#include "DrawingManager.h"
void DrawingManager::addTriangle(const Triangle& triangle) {
    triangles.push_back(triangle);
}
void DrawingManager::calculateLighting(Vertex& vertex) {
    // 计算点积
    float NdotL = vertex.normal.DotProduct(directionalLight_.direction);

    // 将点积限制在 [0, 1] 范围内
    if (NdotL < 0.0f) {
        NdotL = 0.0f;
    }

    // 通过 NdotL 缩放光颜色，计算漫反射光
    Color diffuse = directionalLight_.color * NdotL;

    // 合成顶点颜色与环境光和漫反射光
    /*vertex.color = vertex.color + ambientLight_.color + diffuse;*/
    vertex.color = vertex.color + ambientLight_.color;
}

void DrawingManager::drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) {
    for (auto& vertex : vertices_) {
        calculateLighting(vertex);
    }
  
    //for (const auto& tri : triangles_) {
    //    // 投影三角形的每个顶点到2D坐标

    //    Vertex p1 = Transformer::project(vertices_[std::get<0>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
    //    Vertex p2 = Transformer::project(vertices_[std::get<1>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
    //    Vertex p3 = Transformer::project(vertices_[std::get<2>(tri)], worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);

    //    LineDrawer::drawLine(hdc, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), p1.color, p2.color);
    //    LineDrawer::drawLine(hdc, static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), p2.color, p3.color);
    //    LineDrawer::drawLine(hdc, static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p1.x), static_cast<int>(p1.y), p3.color, p1.color);
    //} 
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

    // 计算三角形的法向量
    Vector edge1 = Vector(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    Vector edge2 = Vector(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    Vector normal = edge1.CrossProduct(edge2);
    normal.normalize();

    // 计算视线方向，这里假设视线方向是 (0, 0, 1)
    Vector viewDir(0, 0, 1);

    // 点积判断背面
    float dotProduct = normal.DotProduct(viewDir);
    if (dotProduct > 0) {
        // 不需要绘制背面
        return;
    }
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