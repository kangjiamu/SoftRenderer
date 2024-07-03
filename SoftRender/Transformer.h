#pragma once
#include "Vertex.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

    static void createViewMatrix(const Vector& p, const Vector& g, const Vector& t, float viewMatrix[4][4]) {
        // Normalizing the direction vectors
        Vector z = g.normalize();                       // Camera forward vector
        Vector x = t.CrossProduct(z).normalize();              // Camera right vector
        Vector y = z.CrossProduct(x);                          // Camera up vector

        // Creating the rotation part of the view matrix
        viewMatrix[0][0] = x.x; viewMatrix[0][1] = y.x; viewMatrix[0][2] = z.x; viewMatrix[0][3] = 0.0f;
        viewMatrix[1][0] = x.y; viewMatrix[1][1] = y.y; viewMatrix[1][2] = z.y; viewMatrix[1][3] = 0.0f;
        viewMatrix[2][0] = x.z; viewMatrix[2][1] = y.z; viewMatrix[2][2] = z.z; viewMatrix[2][3] = 0.0f;
        viewMatrix[3][0] = 0.0f; viewMatrix[3][1] = 0.0f; viewMatrix[3][2] = 0.0f; viewMatrix[3][3] = 1.0f;

        // Creating the translation part of the view matrix
        viewMatrix[3][0] = -x.DotProduct(p);
        viewMatrix[3][1] = -y.DotProduct(p);
        viewMatrix[3][2] = -z.DotProduct(p);
    }
    static void createRotationMatrix(float x, float y, float matrix[4][4]) {
        // 将旋转角度从度转换为弧度
        float angleY = x * 15.0f * (static_cast<float>(M_PI) / 180.0f);
        float angleZ = y * 15.0f * (static_cast<float>(M_PI) / 180.0f);

        // 绕Y轴旋转的矩阵
        float rotationY[4][4] = {
            { cos(angleY), 0, sin(angleY), 0 },
            { 0, 1, 0, 0 },
            { -sin(angleY), 0, cos(angleY), 0 },
            { 0, 0, 0, 1 }
        };

        // 绕Z轴旋转的矩阵
        float rotationZ[4][4] = {
            { cos(angleZ), -sin(angleZ), 0, 0 },
            { sin(angleZ), cos(angleZ), 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 }
        };

        // 初始化结果矩阵为单位矩阵
        createIdentityMatrix(matrix);

        // 合并两个旋转矩阵，顺序：先绕Y轴，再绕Z轴
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matrix[i][j] = 0;
                for (int k = 0; k < 4; ++k) {
                    matrix[i][j] += rotationY[i][k] * rotationZ[k][j];
                }
            }
        }
    }
};