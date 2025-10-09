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
  bool cover(Point p) {return dis(o,p) <= r;}
};