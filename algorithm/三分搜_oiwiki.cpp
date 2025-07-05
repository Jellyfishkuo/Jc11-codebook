//只要是單峰函數，三分可找最大或最小，以下為最小化
//計算lmid以及rmid時要避免數字溢出
while (r - l > eps) { // [l, r]
  mid = (l + r) / 2;
  lmid = mid - eps;
  rmid = mid + eps;
  if (f(lmid) < f(rmid)) r = mid;
  else l = mid;
}