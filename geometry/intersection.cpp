using LL = long long;

struct Point2D {
    LL x, y;
};

struct Line2D {
    Point2D s, e;
    LL a, b, c;             // L: ax + by = c
    Line2D(Point2D s, Point2D e): s(s), e(e) {
        a = e.y - s.y;
        b = s.x - e.x;
        c = a * s.x + b * s.y;
    }
};

// 用克拉馬公式求二元一次解
Point2D intersection2D(Line2D l1, Line2D l2) {
    LL D  = l1.a * l2.b - l2.a * l1.b;
    LL Dx = l1.c * l2.b - l2.c * l1.b;
    LL Dy = l1.a * l2.c - l2.a * l1.c;

    if(D) {          // intersection
        double x = 1.0 * Dx / D;
        double y = 1.0 * Dy / D;
    } else {
        if(Dx || Dy) // Parallel lines
        else         // Same line
    }
}

