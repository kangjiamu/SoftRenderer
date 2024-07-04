#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Vector.h"
#include "Vertex.h"
#include "Color.h"

struct Vec2 {
    float u, v;
};

struct Face {
    std::vector<int> vertexIndices;
    std::vector<int> texCoordIndices;
    std::vector<int> normalIndices;
};

class ObjLoader {
public:
    // 加载OBJ文件
    bool load(const std::string& filename);

    // 打印OBJ文件信息
    void printInfo() const;

private:
    std::vector<Vector> vertices;
    std::vector<Vec2> texCoords;
    std::vector<Vector> normals;
    std::vector<Face> faces;
    std::vector<Vertex> transformedVertices;
};