struct Line {
  Point p;
  Vector v;
  DBL ang;
  Line(Point _p={}, Vector _v={}) {
    p = _p;
    v = _v;
    ang = atan2(v.y, v.x);
  }
  bool operator<(const Line& l) const
  {return ang < l.ang;}
};