#pragma once

#include "Vector.h"
#include "Color.h"

class Vertex {
public:
    Vector position;
    Vector normal;
    float x, y, z, w;
    Color color;
    Vertex(float x = 0, float y = 0, float z = 0, float w = 1) : x(x), y(y), z(z), w(w) {}
   // Vertex();
   // Vertex(float x, float y, float z);
    Vertex transform(const float matrix[4][4]) const {
        float resultX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + w * matrix[3][0];
        float resultY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + w * matrix[3][1];
        float resultZ = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + w * matrix[3][2];
        float resultW = x * matrix[0][3] + y * matrix[1][3] + z * matrix[2][3] + w * matrix[3][3];

        // Í¸ÊÓ³ý·¨
        if (resultW != 0.0f) {
            resultX /= resultW;
            resultY /= resultW;
            resultZ /= resultW;
        }

        return Vertex(resultX, resultY, resultZ, resultW);
    }
};

