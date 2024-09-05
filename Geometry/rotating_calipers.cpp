// 回傳凸包內最遠兩點的距離
int longest_distance(Polygon& p) {
  auto test = [&](Line l, Point a, Point b) {
   return cross(l.v,a-l.p)<=cross(l.v,b-l.p);
  };
  if(p.size() <= 2) {
    return cross(p[0]-p[1], p[0]-p[1]);
  }
  int mx = 0;
  for(int i=0, j=1, n=p.size(); i<n; i++) {
    Line l(p[i], p[(i+1)%n] - p[i]);
    for(;test(l,p[j],p[(j+1)%n]);j=(j+1)%n);
    mx = max({
      mx,
      dot(p[(i+1)%n]-p[j], p[(i+1)%n]-p[j]),
      dot(p[i]-p[j], p[i]-p[j])
    });
  }
  return mx;
}