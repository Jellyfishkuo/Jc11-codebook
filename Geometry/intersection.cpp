int dcmp(DBL a, DBL b=0.0) {
  if(abs(a-b) < eps) return 0;
  return a<b ? -1 : 1;
}

bool hasIntersection(Point p, Segment s) {
  if(dcmp(cross(s.s-p, s.e-p))) return false;
  return dcmp(dot(s.s-p, s.e-p)) <= 0;
}
bool hasIntersection(Point p, Line l) {
  return dcmp(cross(p-l.p, l.v)) == 0;
}
bool hasIntersection(Segment a, Segment b) {
  // 判斷在 X 軸 Y 軸的投影是否相交
  auto intr1D=[](DBL w, DBL x, DBL y, DBL z){
    if(w > x) swap(w, x);
    if(y > z) swap(y, z);
    return dcmp(max(w, y), min(x, z)) <= 0;
  };

  DBL a1 = cross(a.v, b.s-a.s);
  DBL a2 = cross(a.v, b.e-a.s);
  DBL b1 = cross(b.v, a.s-b.s);
  DBL b2 = cross(b.v, a.e-b.s);

  return intr1D(a.s.x, a.e.x, b.s.x, b.e.x)
      && intr1D(a.s.y, a.e.y, b.s.y, b.e.y)
      && dcmp(a1) * dcmp(a2) <= 0
      && dcmp(b1) * dcmp(b2) <= 0;
}

Point intersection(Segment a, Segment b) {
  Vector v = b.s - a.s;
  DBL c1 = cross(a.v, b.v);
  DBL c2 = cross(v, b.v);
  DBL c3 = cross(v, a.v);

  if(dcmp(c1) < 0) c1=-c1, c2=-c2, c3=-c3;
  if(dcmp(c1) && dcmp(c2)>=0 && dcmp(c3)>=0
    && dcmp(c1, c2)>=0 && dcmp(c1, c3)>=0)
    return a.s + (a.v * (c2 / c1));
  return Point(inf, inf);   // a 和 b 共線
}
Point intersection(Line a, Line b) {
  // cross(a.v, b.v) == 0 時平行
  Vector u = a.p - b.p;
  DBL t = 1.0*cross(b.v, u)/cross(a.v, b.v);
  return a.p + a.v*t;
}

DBL dis(Point p, Line l) {
  return abs(cross(p-l.p, l.v))/l.v.length();
}
DBL dis(Point p, Segment s) {
  Vector u = p - s.s, v = p - s.e;
  if(dcmp(dot(s.v, u))<=0) return u.length();
  if(dcmp(dot(s.v, v))>=0) return v.length();
  return abs(cross(s.v, u)) / s.length();
}
DBL dis(Segment a, Segment b) {
  if(hasIntersection(a, b)) return 0;
  return min({
    dis(a.s, b), dis(a.e, b),
    dis(b.s, a), dis(b.e, a)
  });
}
DBL dis(Line a, Line b) {
  if(dcmp(cross(a.v, b.v)) == 0) return 0;
  return dis(a.p, b);
}

// 返回 p 在 l 上的垂足(投影點)
Point getPedal(Line l, Point p) {
  DBL len = dot(p-l.p, l.v) / dot(l.v, l.v);
  return l.p + l.v * len;
}