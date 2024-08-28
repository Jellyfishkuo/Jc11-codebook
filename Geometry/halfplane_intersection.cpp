// Q: 給定一張凸包(已排序的點)，
// 找出圖中離凸包外最遠的距離

using DBL = double;
const DBL pi = acos(-1);
const DBL eps = 1e-8;
const DBL inf = 1e30;
const int maxn = 100 + 10;

struct Vector {
  DBL x, y;
  Vector(DBL x=0.0, DBL y=0.0): x(x), y(y) {}
  DBL length();
  Vector unit_normal_vector() {
    DBL len = length();
    return Vector(-y/len, x/len);
  }
};

Vector operator+(Vector a, Vector b) {
  return Vector(a.x+b.x, a.y+b.y); }
Vector operator-(Vector a, Vector b) {
  return Vector(a.x-b.x, a.y-b.y); }
Vector operator*(Vector a, DBL b) {
  return Vector(a.x*b, a.y*b); }
Vector operator/(Vector a, DBL b) {
  return Vector(a.x/b, a.y/b); }

DBL dot(Vector a, Vector b) {
  return a.x*b.x + a.y*b.y; }
DBL cross(Vector a, Vector b) {
  return a.x*b.y - a.y*b.x; }
DBL Vector::length() {
  return sqrt(dot(*this, *this)); }

using Point = Vector;

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

Point intersection(Line a, Line b) {
  Vector u = a.p - b.p;
  DBL t = cross(b.v, u) / cross(a.v, b.v);
  return a.p + a.v*t;
}

int n, m;

// Receive:
Line nar[maxn];   // 已排序的直線
// Result:
Point poly[maxn]; // 能形成半平面交的凸包邊界點
// Return: poly 的 size
int halfplaneIntersection() {
  sort(nar, nar+n);
  // double val compare with 0
  auto sgn = [](DBL v){return (v>0)-(v<0);};
  // p 是否在 l 的左半平面
  auto lft = [&](Point p, Line l) {
    return sgn(cross(l.v, p-l.p)) > 0;
  };

  int ql = 0, qr = 0;
  Line L[maxn] = {nar[0]};
  Point P[maxn];      // queue 範圍 (ql, qr]

  for(int i=1; i<n; i++) {
    for(; ql<qr&&!lft(P[qr-1],nar[i]); qr--);
    for(; ql<qr&&!lft(P[ql],nar[i]); ql++);
    L[++qr] = nar[i];
    if(sgn(cross(L[qr].v, L[qr-1].v)) == 0) {
      if(lft(nar[i].p,L[--qr])) L[qr]=nar[i];
    }
    if(ql < qr)
      P[qr-1] = intersection(L[qr-1], L[qr]);
  }
  for(; ql<qr && !lft(P[qr-1], L[ql]); qr--);
  if(qr-ql <= 1) return m = 0;
  P[qr] = intersection(L[qr], L[ql]);

  for(m=0; ql<=qr; ) poly[m++] = P[ql++];
  return m;
}

int main() {
  Point p[maxn];        // 輸入點
  Vector vec[maxn];     // 兩點間向量(sorted)
  Vector normal[maxn];  // vec 的單位法向量

  while(~scanf("%d", &n), n) {
    for(int i=0; i<n; i++) {
      scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for(int i=0; i<n; i++) {
      vec[i] = p[(i+1)%n] - p[i];
      normal[i]=vec[i].unit_normal_vector();
    }

    DBL l = 0.0, r = 1e4;
    while((abs(r-l) > eps)) {
      DBL mid = (l + r) / 2;
      for(int i=0; i<n; i++) {
        nar[i] = Line(p[i]+normal[i]*mid, vec[i]);
      }
      if(halfplaneIntersection()) l = mid;
      else r = mid;
    }

    printf("%.6lf\n", l);
  }
}