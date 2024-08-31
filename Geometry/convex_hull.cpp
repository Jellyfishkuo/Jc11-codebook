using TP = long long;
using Polygon = vector<Point>;

const TP inf = 1e9;     // 座標點最大值

Polygon convex_hull(Point* p, int n) {
  auto dblcmp = [](DBL a, DBL b=0.0) {
    return (a>b) - (a<b);
  };
  auto rmv = [&](Point a, Point b, Point c) {
    return cross(b-a, c-b) <= 0;  // 非浮點數
    return dblcmp(cross(b-a, c-b)) <= 0;
  };

  // 選最下裡最左的當基準點，可在輸入時計算
  TP lx = inf, ly = inf;
  for(int i=0; i<n; i++) {
    if(p[i].y<ly || (p[i].y==ly&&p[i].x<lx)){
      lx = p[i].x, ly = p[i].y;
    } 
  }

  for(int i=0; i<n; i++) {
    p[i].ang=atan2(p[i].y-ly,p[i].x-lx);
    p[i].d2 = (p[i].x-lx)*(p[i].x-lx) +
              (p[i].y-ly)*(p[i].y-ly);
  }
  sort(p, p+n, [&](Point& a, Point& b) {
    if(dblcmp(a.ang, b.ang))
      return a.ang < b.ang;
    return a.d2 < b.d2;
  });

  int m = 1;     // stack size
  Point st[n] = {p[n]=p[0]};
  for(int i=1; i<=n; i++) {
    for(;m>1&&rmv(st[m-2],st[m-1],p[i]);m--);
    st[m++] = p[i];
  }
  return Polygon(st, st+m-1);
}