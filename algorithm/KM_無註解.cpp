#define maxn 505
int W[maxn][maxn];
int Lx[maxn], Ly[maxn];
bool S[maxn], T[maxn];
//L[i] = j -> S_i配給T_j, -1 for 還沒匹配
int L[maxn];
int n;
bool match(int i) {
  S[i] = true;
  for (int j = 0; j < n; ++j) {
    // KM重點
    // Lx + Ly >= selected_edge(x, y)
    // 要想辦法降低Lx + Ly
    // 所以選Lx + Ly == selected_edge(x, y)
    if (Lx[i] + Ly[j] == W[i][j] && !T[j]) {
      T[j] = true;
      if ((L[j] == -1) || match(L[j])) {
        L[j] = i;
        return true;
      }
    }
  }
  return false;
}
//修改二分圖上的交錯路徑上點的權重
//此舉是在通過調整vertex labeling看看
//能不能產生出新的增廣路
//(KM的增廣路要求Lx[i] + Ly[j] == W[i][j])
//在這裡優先從最小的diff調調看，才能保證最大權重匹配
void update() {
  int diff = 0x3f3f3f3f;
  for (int i = 0; i < n; ++i) {
    if (S[i]) {
      for (int j = 0; j < n; ++j) {
        if (!T[j]) diff = min(diff, Lx[i] + Ly[j] - W[i][j]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (S[i]) Lx[i] -= diff;
    if (T[i]) Ly[i] += diff;
  }
}
void KM() {
  for (int i = 0; i < n; ++i) {
    L[i] = -1;
    Lx[i] = Ly[i] = 0;
    for (int j = 0; j < n; ++j)
      Lx[i] = max(Lx[i], W[i][j]);
  }
  for (int i = 0; i < n; ++i) {
    while(1) {
      memset(S, false, sizeof(S));
      memset(T, false, sizeof(T));
      if (match(i)) break;
      else update(); //去調整vertex labeling以增加增廣路徑
    }
  }
}
int main() {
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%d", &W[i][j]);
    KM();
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (i != 0) printf(" %d", Lx[i]);
      else printf("%d", Lx[i]);
      res += Lx[i];
    }
    puts("");
    for (int i = 0; i < n; ++i) {
      if (i != 0) printf(" %d", Ly[i]);
      else printf("%d", Ly[i]);
      res += Ly[i];
    }
    puts("");
    printf("%d\n", res);
  }
  return 0;
}