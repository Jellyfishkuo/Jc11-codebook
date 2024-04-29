// Q: 給定一張凸包(以排序的點)，找出圖中離凸包外最遠的距離

#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 10;
const double eps = 1e-7;

struct Vector {
    double x, y;
    Vector(double x=0.0, double y=0.0): x(x), y(y) {}

    Vector operator+(Vector v) {
        return Vector(x+v.x, y+v.y);
    }
    Vector operator-(Vector v) {
        return Vector(x-v.x, y-v.y);
    }
    Vector operator*(double val) {
        return Vector(x*val, y*val);
    }
    double dot(Vector v) { return x*v.x + y*v.y; }
    double cross(Vector v) { return x*v.y - y*v.x; }
    double length() { return sqrt(dot(*this)); }
    Vector unit_normal_vector() {
        double len = length();
        return Vector(-y/len, x/len);
    }
};

using Point = Vector;

struct Line {
    Point p;
    Vector v;
    double ang;
    Line(Point p={}, Vector v={}): p(p), v(v) {
        ang = atan2(v.y, v.x);
    }
    bool operator<(const Line& l) const {
        return ang < l.ang;
    }
    Point intersection(Line l) {
        Vector u = p - l.p;
        double t = l.v.cross(u) / v.cross(l.v);
        return p + v*t;
    }
};

int n, m;
Line narrow[maxn];      // 要判斷的直線
Point poly[maxn];       // 能形成半平面交的凸包邊界點

// return true if point p is on the left of line l
bool onLeft(Point p, Line l) {
    return l.v.cross(p-l.p) > 0;
}

int halfplaneIntersection() {
    int l, r;
    Line L[maxn];   // 排序後的向量隊列
    Point P[maxn];  // s[i] 跟 s[i-1] 的交點

    L[l=r=0] = narrow[0];  // notice: narrow is sorted
    for(int i=1; i<n; i++) {
        while(l<r && !onLeft(P[r-1], narrow[i])) r--;
        while(l<r && !onLeft(P[l], narrow[i])) l++;

        L[++r] = narrow[i];
        if(l < r) P[r-1] = L[r-1].intersection(L[r]);
    }

    while(l<r && !onLeft(P[r-1], L[l])) r--;
    if(r-l <= 1) return 0;

    P[r] = L[r].intersection(L[l]);

    int m=0;
    for(int i=l; i<=r; i++) {
        poly[m++] = P[i];
    }

    return m;
}

Point pt[maxn];
Vector vec[maxn];
Vector normal[maxn]; // normal[i] = vec[i] 的單位法向量

double bsearch(double l=0.0, double r=1e4) {
    if(abs(r-l) < 1e-7) return l;
    
    double mid = (l + r) / 2;

    for(int i=0; i<n; i++) {
        narrow[i] = Line(pt[i]+normal[i]*mid, vec[i]);
    }

    if(halfplaneIntersection())
        return bsearch(mid, r);
    else return bsearch(l, mid);
}

int main() {
    while(~scanf("%d", &n) && n) {
        for(int i=0; i<n; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            pt[i] = {x, y};
        }
        for(int i=0; i<n; i++) {
            vec[i] = pt[(i+1)%n] - pt[i];
            normal[i] = vec[i].unit_normal_vector();
        }

        printf("%.6lf\n", bsearch());
    }
    return 0;
}