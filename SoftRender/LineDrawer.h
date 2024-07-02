#pragma once
// 使用DDA算法的画线类
class LineDrawer {
public:
    static void drawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = max(abs(dx), abs(dy));
        float xIncrement = dx / (float)steps;
        float yIncrement = dy / (float)steps;

        float x = x1;
        float y = y1;
        for (int i = 0; i <= steps; i++) {
            SetPixel(hdc, static_cast<int>(x), static_cast<int>(y), color);
            x += xIncrement;
            y += yIncrement;
        }
    }
};