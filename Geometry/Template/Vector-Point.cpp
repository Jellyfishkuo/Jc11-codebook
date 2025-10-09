struct Vector {
  Tp x, y;
  Vector(Tp x=0, Tp y=0): x(x), y(y) {}
  DBL length();
};

using Point = Vector;
using Polygon = vector<Point>;

Vector operator+(Vector a, Vector b)
{return Vector(a.x+b.x, a.y+b.y);}
Vector operator-(Vector a, Vector b)
{return Vector(a.x-b.x, a.y-b.y);}
Vector operator*(Vector a, DBL b)
{return Vector(a.x*b, a.y*b);}
Vector operator/(Vector a, DBL b)
{return Vector(a.x/b, a.y/b);}
Tp dot(Vector a, Vector b)
{return a.x*b.x + a.y*b.y;}
Tp cross(Vector a, Vector b)
{return a.x*b.y - a.y*b.x;}
DBL Vector::length()
{return sqrt(dot(*this, *this));}
Vector unit_normal_vector(Vector v) {
  DBL len = v.length();
  return Vector(-v.y/len, v.x/len);
}