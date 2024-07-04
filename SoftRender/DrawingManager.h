#pragma once
#include "Transformer.h"
#include "Light.h"
#include "Triangle.h"
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
    

    void addTriangle(const Triangle& triangle);
    void calculateLighting(Vertex& vertex);
    void drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight);
    void setAmbientLight(const Color& color);
    void setDirectionalLight(const Vector& direction, const Color& color);
    void addTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
   
};