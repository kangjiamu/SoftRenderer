#pragma once
#include "Vertex.h"
class Transformer {
public:
    static Vertex project(const Vertex& vertex, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) {
        Vertex transformedVertex = vertex.transform(worldMatrix).transform(viewMatrix).transform(projMatrix);

        // 视口变换，将归一化设备坐标(ndc)转换为屏幕坐标
        float x = (transformedVertex.x + 1) * 0.5f * viewportWidth;
        float y = viewportHeight - (transformedVertex.y + 1) * 0.5f * viewportWidth;  // 注意坐标系的翻转
        return Vertex(x, y);
    }

    // 创建透视投影矩阵
    static void createPerspectiveProjMatrix(float fovY, float aspect, float nearZ, float farZ, float matrix[4][4]) {
        float tanHalfFovy = tan(fovY / 2.0f);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = 0.0f;
            }
        }

        matrix[0][0] = 1.0f / (aspect * tanHalfFovy);
        matrix[1][1] = 1.0f / tanHalfFovy;
        matrix[2][2] = farZ / (farZ - nearZ);
        matrix[2][3] = 1.0f;
        matrix[3][2] = -(farZ * nearZ) / (farZ - nearZ);
    }

    // 创建单位矩阵
    static void createIdentityMatrix(float matrix[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    // 创建平移矩阵
    static void createTranslationMatrix(float tx, float ty, float tz, float matrix[4][4]) {
        createIdentityMatrix(matrix);
        matrix[3][0] = tx;
        matrix[3][1] = ty;
        matrix[3][2] = tz;
    }
};