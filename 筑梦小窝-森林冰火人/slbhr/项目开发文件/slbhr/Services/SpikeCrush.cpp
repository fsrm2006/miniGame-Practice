// 判断点(px, py)是否在矩形内
bool PointInRect(int px, int py, int rx1, int ry1, int rx2, int ry2) {
    return px >= rx1 && px <= rx2 && py >= ry1 && py <= ry2;
}

// 叉积辅助函数
int Cross(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

// 判断点(px, py)是否在三角形内
bool PointInTriangle(int px, int py, int x1, int y1, int x2, int y2, int x3, int y3) {
    int d1 = Cross(x2 - x1, y2 - y1, px - x1, py - y1);
    int d2 = Cross(x3 - x2, y3 - y2, px - x2, py - y2);
    int d3 = Cross(x1 - x3, y1 - y3, px - x3, py - y3);
    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(has_neg && has_pos);
}

// 判断两线段是否相交
bool SegmentsIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    auto cross = [](int x1, int y1, int x2, int y2) {
        return x1 * y2 - x2 * y1;
        };
    int d1 = cross(x4 - x3, y4 - y3, x1 - x3, y1 - y3);
    int d2 = cross(x4 - x3, y4 - y3, x2 - x3, y2 - y3);
    int d3 = cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
    int d4 = cross(x2 - x1, y2 - y1, x4 - x1, y4 - y1);
    return (d1 * d2 < 0) && (d3 * d4 < 0);
}

// 主函数：矩形与三角形碰撞检测
bool RectTriangleCollide(
    int x1, int y1, int x2, int y2, int x3, int y3, // 三角形顶点
    int rx1, int ry1, int rx2, int ry2              // 矩形左上、右下
) {
    // 1. 三角形顶点是否在矩形内
    if (PointInRect(x1, y1, rx1, ry1, rx2, ry2) ||
        PointInRect(x2, y2, rx1, ry1, rx2, ry2) ||
        PointInRect(x3, y3, rx1, ry1, rx2, ry2))
        return true;

    // 2. 矩形四个顶点是否在三角形内
    if (PointInTriangle(rx1, ry1, x1, y1, x2, y2, x3, y3) ||
        PointInTriangle(rx2, ry1, x1, y1, x2, y2, x3, y3) ||
        PointInTriangle(rx2, ry2, x1, y1, x2, y2, x3, y3) ||
        PointInTriangle(rx1, ry2, x1, y1, x2, y2, x3, y3))
        return true;

    // 3. 三角形三条边与矩形四条边是否有交点
    int tri[3][2] = { {x1, y1}, {x2, y2}, {x3, y3} };
    int rect[4][2] = { {rx1, ry1}, {rx2, ry1}, {rx2, ry2}, {rx1, ry2} };
    for (int i = 0; i < 3; ++i) {
        int tx1 = tri[i][0], ty1 = tri[i][1];
        int tx2 = tri[(i + 1) % 3][0], ty2 = tri[(i + 1) % 3][1];
        for (int j = 0; j < 4; ++j) {
            int rxA = rect[j][0], ryA = rect[j][1];
            int rxB = rect[(j + 1) % 4][0], ryB = rect[(j + 1) % 4][1];
            if (SegmentsIntersect(tx1, ty1, tx2, ty2, rxA, ryA, rxB, ryB))
                return true;
        }
    }
    return false;
}