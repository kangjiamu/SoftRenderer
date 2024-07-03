#pragma once
#include "Vertex.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Transformer {
public:
    static Vertex project(const Vertex& vertex, const float worldMatrix[4][4], const float viewMatrix[4][4], const float projMatrix[4][4], int viewportWidth, int viewportHeight) {
        Vertex transformedVertex = vertex.transform(worldMatrix).transform(viewMatrix).transform(projMatrix);

        // �ӿڱ任������һ���豸����(ndc)ת��Ϊ��Ļ����
        float x = (transformedVertex.x + 1) * 0.5f * viewportWidth;
        float y = viewportHeight - (transformedVertex.y + 1) * 0.5f * viewportWidth;  // ע������ϵ�ķ�ת
        return Vertex(x, y);
    }

    // ����͸��ͶӰ����
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

    // ������λ����
    static void createIdentityMatrix(float matrix[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    // ����ƽ�ƾ���
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
        // ����ת�ǶȴӶ�ת��Ϊ����
        float angleY = x * 15.0f * (static_cast<float>(M_PI) / 180.0f);
        float angleZ = y * 15.0f * (static_cast<float>(M_PI) / 180.0f);

        // ��Y����ת�ľ���
        float rotationY[4][4] = {
            { cos(angleY), 0, sin(angleY), 0 },
            { 0, 1, 0, 0 },
            { -sin(angleY), 0, cos(angleY), 0 },
            { 0, 0, 0, 1 }
        };

        // ��Z����ת�ľ���
        float rotationZ[4][4] = {
            { cos(angleZ), -sin(angleZ), 0, 0 },
            { sin(angleZ), cos(angleZ), 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 1 }
        };

        // ��ʼ���������Ϊ��λ����
        createIdentityMatrix(matrix);

        // �ϲ�������ת����˳������Y�ᣬ����Z��
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