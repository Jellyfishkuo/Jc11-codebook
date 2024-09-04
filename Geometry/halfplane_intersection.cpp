using DBL = double;
using TP = DBL;   // 存點的型態
using Polygon = vector<Point>;

const int maxn = 5e4 + 10;

// Return: 能形成半平面交的凸包邊界點
Polygon halfplaneIntersect(vector<Line>&nar){
  sort(nar.begin(), nar.end());
  // DBL 跟 0 比較, 沒符點數不用
  auto dblcmp=[](DBL v){return (v>0)-(v<0);};
  // p 是否在 l 的左半平面
  auto lft = [&](Point p, Line l) {
    return dblcmp(cross(l.v, p-l.p)) > 0;
  };

  int ql = 0, qr = 0;
  Line L[maxn] = {nar[0]};
  Point P[maxn]; 

  for(int i=1; i<nar.size(); i++) {
    for(; ql<qr&&!lft(P[qr-1],nar[i]); qr--);
    for(; ql<qr&&!lft(P[ql],nar[i]); ql++);
    L[++qr] = nar[i];
    if(dblcmp(cross(L[qr].v,L[qr-1].v))==0) {
      if(lft(nar[i].p,L[--qr])) L[qr]=nar[i];
    }
    if(ql < qr)
      P[qr-1] = intersection(L[qr-1], L[qr]);
  }
  for(; ql<qr && !lft(P[qr-1], L[ql]); qr--);
  if(qr-ql <= 1) return {};
  P[qr] = intersection(L[qr], L[ql]);
  return Polygon(P+ql, P+qr+1);
}