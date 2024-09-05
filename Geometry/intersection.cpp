// 除 intersection(Line a, Line b) 之外，
// 皆尚未丟 online judge

int dcmp(DBL a, DBL b=0.0) {
  return (a > b) - (a < b);
}

bool hasIntersection(Point p, Segment s) {
  return dcmp(cross(p-s.s, s.s-s.e))==0&&
         dcmp(dot(p.x-s.s.x, p.x-s.e.x))<=0&&
         dcmp(dot(p.y-s.s.y, p.y-s.e.y))<=0;
}

bool hasIntersection(Point p, Line l) {
  return dcmp(cross(p-l.p, l.v)) == 0;
}

DBL dis(Line l, Point p) {
  DBL t = cross(p, l.v) + cross(l.v, l.p);
  return abs(t) / sqrt(dot(l.v, l.v));
}

Point intersection(Line a, Line b) {
  Vector u = a.p - b.p;
  DBL t = 1.0*cross(b.v, u)/cross(a.v, b.v);
  return a.p + a.v*t;
}