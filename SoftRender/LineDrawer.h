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
    
    static void drawLine(HDC hdc, int x0, int y0, int x1, int y1, const Color &c0, const Color &c1) {
   
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;
        int length = max(dx, dy);
        for (int i = 0; i <= length; ++i) {
            float t = static_cast<float>(i) / length;
            Color color = Color::interpolate(c0, c1, t);
            SetPixel(hdc, x0, y0, RGB(color.r * 255, color.g * 255, color.b * 255));
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 < dx) { err += dx; y0 += sy; }
        }
    }
};