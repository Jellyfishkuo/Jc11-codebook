using DBL = double;
using TP = DBL;   // 存點的型態

const DBL pi = acos(-1);
const DBL eps = 1e-8;
const TP inf = 1e30;
const int maxn = 5e4 + 10;

struct Vector {
  TP x, y;
  Vector(TP x=0, TP y=0): x(x), y(y) {}
  DBL length();
};
using Point = Vector;
using Polygon = vector<Point>;

Vector operator+(Vector a, Vector b) {
  return Vector(a.x+b.x, a.y+b.y); }
Vector operator-(Vector a, Vector b) {
  return Vector(a.x-b.x, a.y-b.y); }
Vector operator*(Vector a, DBL b) {
  return Vector(a.x*b, a.y*b); }
Vector operator/(Vector a, DBL b) {
  return Vector(a.x/b, a.y/b); }

TP dot(Vector a, Vector b) {
  return a.x*b.x + a.y*b.y;
}
TP cross(Vector a, Vector b) {
  return a.x*b.y - a.y*b.x;
}
DBL Vector::length() {
  return sqrt(dot(*this, *this));
}
DBL dis(Point a, Point b) {
  return sqrt(dot(a-b, a-b));
}
Vector unit_normal_vector(Vector v) {
  DBL len = v.length();
  return Vector(-v.y/len, v.x/len);
}

struct Line {
  Point p;
  Vector v;
  DBL ang;
  Line(Point _p={}, Vector _v={}) {
    p = _p;
    v = _v;
    ang = atan2(v.y, v.x);
  }
  bool operator<(const Line& l) const {
    return ang < l.ang;
  }
};

struct Circle {
  Point o;
  DBL r;
  Circle(): o({0, 0}), r(0) {}
  Circle(Point o, DBL r=0): o(o), r(r) {}
  Circle(Point a, Point b) {    // ab 直徑
    o = (a + b) / 2;
    r = dis(o, a);
  }
  Circle(Point a, Point b, Point c) {
    Vector u = b-a, v = c-a;
    DBL c1=dot(u, a+b)/2, c2=dot(v, a+c)/2;
    DBL dx=c1*v.y-c2*u.y, dy=u.x*c2-v.x*c1;
    o = Point(dx, dy) / cross(u, v);
    r = dis(o, a);
  }
  bool cover(Point p) {
    return dis(o, p) <= r;
  }
};