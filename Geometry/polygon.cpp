// 判斷點 (point) 是否在凸包 (p) 內
bool pointInConvex(Polygon& p, Point point) {
  // 根據 TP 型態來寫，沒浮點數不用 dblcmp
  auto dblcmp=[](DBL v){return (v>0)-(v<0);};
  // 不包含線上，改 '>=' 為 '<'
  auto test = [&](Point& p0, Point& p1) {
    return dblcmp(cross(p1-p0, point-p0))>=0;
  };
  p.push_back(p[0]);
  for(int i=1; i<p.size(); i++) {
    if(!test(p[i-1], p[i])) {
      p.pop_back();
      return false;
    }
  }
  p.pop_back();
  return true;
}

// 計算簡單多邊形的面積
// ! p 為排序過的點 !
DBL polygonArea(Polygon& p) {
  DBL sum = 0;
  for(int i=0, n=p.size(); i<n; i++)
    sum += cross(p[i], p[(i+1)%n]);
  return abs(sum) / 2.0;
}