vector<Point> p(3);     // 在圓上的點
Circle MEC(vector<Point>& v, int n, int d=0){
  Circle mec;
  if(d == 1) mec = Circle(p[0]);
  if(d == 2) mec = Circle(p[0], p[1]);
  if(d == 3) return Circle(p[0], p[1], p[2]);
  for(int i=0; i<n; i++) {
    if(mec.cover(v[i])) continue;
    p[d] = v[i];
    mec = MEC(v, i, d+1);
  }
  return mec;
}