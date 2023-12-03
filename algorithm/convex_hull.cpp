/* ***************************************************
 * 問題：在平面上給定多區域，再給定多點(x, y)，
 * 判斷有落點的區域(destroyed)的面積總和。
 * **************************************************/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 10;
const int maxCoordinate = 500 + 10;

struct Point {
    int x, y;
};

int n;
bool destroyed[maxn] = {};
Point arr[maxn];
vector<Point> polygons[maxn];

void scanAndSortPoints() {
    int minX = maxCoordinate, minY = maxCoordinate;
    for(int i=0; i<n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        arr[i] = (Point){x, y};
        if(y < minY || (y == minY && x < minX)) {
    //  If there are floating points, use:
    //  if(y<minY || (fabs(y-minY)<eps && x<minX)) {
            minX = x, minY = y;
        }
    }
    sort(arr, arr+n, [minX, minY](Point& a, Point& b){
        double theta1 = atan2(a.y - minY, a.x - minX);
        double theta2 = atan2(b.y - minY, b.x - minX);
        return theta1 < theta2;
    });
    return;
}

//  returns u(AB) x v(AC)
int cross(Point& A, Point& B, Point& C) {
    int u[2] = {B.x - A.x, B.y - A.y};
    int v[2] = {C.x - A.x, C.y - A.y};
    return (u[0] * v[1]) - (u[1] * v[0]);
}

// size of arr >= 3
// st = the stack using vector, m = index of the top
vector<Point> convex_hull() {
    vector<Point> st(arr, arr+3);
    for(int i=3, m=2; i<n; i++, m++) {
        while(m >= 2) {
            if(cross(st[m], st[m-1], arr[i]) < 0)
                break;
            st.pop_back();
            m--;
        }
        st.push_back(arr[i]);
    }
    return st;
}

bool inPolygon(vector<Point>& vec, Point p) {
    vec.push_back(vec[0]);
    for(int i=1; i<vec.size(); i++) {
        if(cross(vec[i-1], vec[i], p) < 0) {
            vec.pop_back();
            return false;
        }
    }
    vec.pop_back();
    return true;
}

/* ***************************************************
 *        1 | x1   x2   x3   x4   x5         xn |
 *    A = — |    x    x    x    x    x ... x    |
 *        2 | y1   y2   y3   y4   y5         yn |
 * **************************************************/
double calculateArea(vector<Point>& v) {
    v.push_back(v[0]);
    double result = 0.0;
    for(int i=1; i<v.size(); i++)
        result += v[i-1].x*v[i].y - v[i-1].y*v[i].x;
    v.pop_back();
    return result / 2.0;
}

int main() {
    int p = 0;
    while(~scanf("%d", &n) && (n != -1)) {
        scanAndSortPoints();
        polygons[p++] = convex_hull();
    }

    int x, y;
    double result = 0.0;
    while(~scanf("%d%d", &x, &y)) {
        for(int i=0; i<p; i++) {
            if(inPolygon(polygons[i], (Point){x, y}))
                destroyed[i] = true;
        }
    }
    for(int i=0; i<p; i++) {
        if(destroyed[i])
            result += calculateArea(polygons[i]);
    }
    printf("%.2lf\n", result);
    return 0;
}