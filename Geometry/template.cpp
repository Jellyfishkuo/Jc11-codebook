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
Vector unit_normal_vector(Vector v) {
  DBL len = v.length();
  return Vector(-v.y/len, v.x/len);
}

using Point = Vector;
using Polygon = vector<Point>;

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