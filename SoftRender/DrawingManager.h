#pragma once
#include "Transformer.h"
#include "Light.h"
#include <vector>
#include <tuple>
class DrawingManager {
private:
    AmbientLight ambientLight_;
    DirectionalLight directionalLight_;
public:
    //DrawingManger(AmbientLight alight, DirectionalLight dlight) : ambientLight_(alight), directionalLight_(dlight) {};

    std::vector<Triangle> triangles;
    
    std::vector<Vertex> vertices_;
    std::vector<std::tuple<int, int, int>> triangles_;

    void addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    } 
    void calculateLighting(Vertex& vertex) {
        float NdotL = 0.0f > vertex.normal.DotProduct(directionalLight_.direction) ? 0.0f : vertex.normal.DotProduct(directionalLight_.direction);
        Color diffuse = directionalLight_.color * NdotL;
        vertex.color = vertex.color + ambientLight_.color + diffuse;
    }

    void drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) {
         for (auto& vertex : vertices_) {
            calculateLighting(vertex);
         }
          /*
         for (const auto& triangle : triangles) {
            // 投影三角形的每个顶点到2D坐标
            Vertex p1 = Transformer::project(triangle.v0, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
            Vertex p2 = Transformer::project(triangle.v1, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);
            Vertex p3 = Transformer::project(triangle.v2, worldMatrix, viewMatrix, projMatrix, viewportWidth, viewportHeight);

            LineDrawer::drawLine(hdc, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), RGB(255, 0, 0));
            LineDrawer::drawLine(hdc, static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), RGB(255, 0, 0));
            LineDrawer::drawLine(hdc, static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p1.x), static_cast<int>(p1.y), RGB(255, 0, 0));

            LineDrawer::drawLine(hdc, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y), p1.color, p2.color);
            LineDrawer::drawLine(hdc, static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p3.x), static_cast<int>(p3.y), p2.color, p3.color);
            LineDrawer::drawLine(hdc, static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p1.x), static_cast<int>(p1.y), p3.color, p1.color);
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
    }
    void setAmbientLight(const Color& color) {
        ambientLight_.color = color;
    }

    void setDirectionalLight(const Vector& direction, const Color& color) {
        directionalLight_.direction = direction.normalize();
        directionalLight_.color = color;
    }
    void addTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2) {
        int idx = vertices_.size();
        vertices_.emplace_back(v0);
        vertices_.emplace_back(v1);
        vertices_.emplace_back(v2);
        triangles_.emplace_back(idx, idx + 1, idx + 2);
    }
};