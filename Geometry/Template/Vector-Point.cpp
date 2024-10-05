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