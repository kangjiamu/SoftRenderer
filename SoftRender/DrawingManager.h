#pragma once
#include "Transformer.h"
#include "Light.h"
#include "Triangle.h"
#include "ObjLoader.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <tuple>

class DrawingManager {
private:
    AmbientLight ambientLight_;
    DirectionalLight directionalLight_;
public:
    DrawingManager(int width, int height)
        : width_(width), height_(height), depthBuffer_(width* height, std::numeric_limits<float>::infinity()) {}
    //DrawingManger(AmbientLight alight, DirectionalLight dlight) : ambientLight_(alight), directionalLight_(dlight) {};

    std::vector<Triangle> triangles;
    
    std::vector<Vertex> vertices_;
    std::vector<std::tuple<int, int, int>> triangles_;
    int width_;
    int height_;
    std::vector<float> depthBuffer_;
    

    void addTriangle(const Triangle& triangle);
    void calculateLighting(Vertex& vertex);
    void drawAll(HDC hdc, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight);
    void setAmbientLight(const Color& color);
    void setDirectionalLight(const Vector& direction, const Color& color);
    void addTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
    void loadObjFile(const std::string& filename) {
        ObjLoader objLoader;
        if (!objLoader.load(filename)) {
            std::cerr << "Failed to load OBJ file: " << filename << std::endl;
            return;
        }
    }

    bool computeBarycentricCoordinates(float x, float y, const Vertex& v0, const Vertex& v1, const Vertex& v2, float& w0, float& w1, float& w2) {
        float denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
        w0 = ((v1.y - v2.y) * (x - v2.x) + (v2.x - v1.x) * (y - v2.y)) / denom;
        w1 = ((v2.y - v0.y) * (x - v2.x) + (v0.x - v2.x) * (y - v2.y)) / denom;
        w2 = 1.0f - w0 - w1;

        // 如果重心坐标在 [0, 1] 范围内，则表示点在三角形内部
        return (w0 >= 0) && (w1 >= 0) && (w2 >= 0);
    }
    float myMin(std::initializer_list<float> values) {
        return *std::min_element(values.begin(), values.end());
    }


    float myMax(std::initializer_list<float> values) {
        return *std::max_element(values.begin(), values.end());
    }
    void drawTriangle(HDC hdc, const Vertex& v0, const Vertex& v1, const Vertex& v2);
   
    
};