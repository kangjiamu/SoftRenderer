#include "ObjLoader.h"

// ����OBJ�ļ�ʵ��
bool ObjLoader::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream linestream(line);
        std::string prefix;
        linestream >> prefix;

        if (prefix == "v") {
            // ����
            float x, y, z;
            linestream >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (prefix == "vt") {
            // ��������
            float u, v;
            linestream >> u >> v;
            texCoords.push_back({ u, v });
        }
        else if (prefix == "vn") {
            // ����
            float x, y, z;
            linestream >> x >> y >> z;
            normals.emplace_back(x, y, z);
        }
        else if (prefix == "f") {
            // ��
            Face face;
            std::string vertexInfo;
            while (linestream >> vertexInfo) {
                size_t slash1 = vertexInfo.find('/');
                size_t slash2 = vertexInfo.find('/', slash1 + 1);

                int vertexIndex = std::stoi(vertexInfo.substr(0, slash1)) - 1;
                int texCoordIndex = (slash1 != std::string::npos && slash2 != std::string::npos) ? std::stoi(vertexInfo.substr(slash1 + 1, slash2 - slash1 - 1)) - 1 : -1;
                int normalIndex = (slash2 != std::string::npos) ? std::stoi(vertexInfo.substr(slash2 + 1)) - 1 : -1;

                face.vertexIndices.push_back(vertexIndex);
                if (texCoordIndex >= 0) face.texCoordIndices.push_back(texCoordIndex);
                if (normalIndex >= 0) face.normalIndices.push_back(normalIndex);
            }
            faces.push_back(face);
        }
    }

    // ������ת��Ϊ Vertex ��
    for (const auto& face : faces) {
        for (size_t i = 0; i < face.vertexIndices.size(); i++) {
            int vertexIndex = face.vertexIndices[i];
            int texCoordIndex = (i < face.texCoordIndices.size()) ? face.texCoordIndices[i] : -1;
            int normalIndex = (i < face.normalIndices.size()) ? face.normalIndices[i] : -1;

            Vector normal = (normalIndex >= 0) ? normals[normalIndex] : Vector();
            Vec2 texCoord = (texCoordIndex >= 0) ? texCoords[texCoordIndex] : Vec2{ 0, 0 };
            Color color(texCoord.u, texCoord.v, 0.0f); // ������� `Color` �����е���

            transformedVertices.emplace_back(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z, 1.0f, normal, color);
        }
    }

    return true;
}

// ��ӡOBJ�ļ���Ϣʵ��
void ObjLoader::printInfo() const {
    std::cout << "Vertices: " << vertices.size() << std::endl;
    std::cout << "Texture coordinates: " << texCoords.size() << std::endl;
    std::cout << "Normals: " << normals.size() << std::endl;
    std::cout << "Faces: " << faces.size() << std::endl;

    std::cout << "Transformed Vertices: " << transformedVertices.size() << std::endl;
    for (const Vertex& v : transformedVertices) {
        std::cout << "Vertex: (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
        v.normal.print();
        std::cout << "Color: (" << v.color.r << ", " << v.color.g << ", " << v.color.b << ")" << std::endl;
    }
}