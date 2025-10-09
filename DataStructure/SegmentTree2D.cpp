#define maxn 2005 //500 * 4 + 5 //純2D segment tree 區間查詢單點修改最大最小值
int maxST[maxn][maxn], minST[maxn][maxn];
int N;
void modifyY(int index, int l, int r,int val,
  int yPos, int xIndex, bool xIsLeaf) {
  if (l == r) {
    if (xIsLeaf) {
      maxST[xIndex][index] = minST[xIndex][index] = val;
      return;
    }
    maxST[xIndex][index] = max(maxST[xIndex*2][index], maxST[xIndex*2 + 1][index]);
    minST[xIndex][index] = min(minST[xIndex*2][index], minST[xIndex*2 + 1][index]);
  }
  else {
    int mid = (l + r) / 2;
    if (yPos <= mid)
      modifyY(index*2, l, mid, val, yPos, xIndex, xIsLeaf);
    else
      modifyY(index*2 + 1, mid + 1, r, val, yPos, xIndex, xIsLeaf);
    maxST[xIndex][index] = max(maxST[xIndex][index*2], maxST[xIndex][index*2 + 1]);
    minST[xIndex][index] = min(minST[xIndex][index*2], minST[xIndex][index*2 + 1]);
  }
}
void modifyX(int index, int l, int r, int val, int xPos, int yPos) {
  if (l == r) {
    modifyY(1, 1, N, val, yPos, index, true);
  }
  else {
    int mid = (l + r) / 2;
    if (xPos <= mid)
      modifyX(index*2,l,mid,val,xPos,yPos);
    else
      modifyX(index*2 + 1, mid + 1, r, val, xPos, yPos);
    modifyY(1, 1, N, val, yPos, index,false);
  }
}
void queryY(int index, int l, int r,int yql,
  int yqr, int xIndex, int& vmax, int &vmin){
  if (yql <= l && r <= yqr) {
    vmax = max(vmax, maxST[xIndex][index]);
    vmin = min(vmin, minST[xIndex][index]);
  }
  else {
    int mid = (l + r) / 2;
    if (yql <= mid)
      queryY(index*2, l, mid, yql, yqr, xIndex, vmax, vmin);
    if (mid < yqr)
      queryY(index*2 + 1, mid + 1, r, yql, yqr, xIndex, vmax, vmin);
  }
}
void queryX(int index, int l, int r, int xql, int xqr, int yql, int yqr, int& vmax, int& vmin) {
  if (xql <= l && r <= xqr) {
    queryY(1,1,N,yql,yqr,index,vmax,vmin);
  }
  else {
    int mid = (l + r) / 2;
    if (xql <= mid)
      queryX(index*2, l, mid, xql, xqr, yql, yqr, vmax, vmin);
    if (mid < xqr)
      queryX(index*2 + 1, mid + 1, r, xql, xqr, yql, yqr, vmax, vmin);
  }
}
int main() {
  while (scanf("%d", &N) != EOF) {
    int val;
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        scanf("%d", &val);
        modifyX(1, 1, N, val, i, j);
      }
    }
    int q;
    int vmax, vmin;
    int xql, xqr, yql, yqr;
    char op;
    scanf("%d", &q);
    while (q--) {
      getchar(); //for \n
      scanf("%c", &op);
      if (op == 'q') {
        scanf("%d %d %d %d", &xql, &yql, &xqr, &yqr);
        vmax = -0x3f3f3f3f;
        vmin =  0x3f3f3f3f;
        queryX(1, 1, N, xql, xqr, yql, yqr, vmax, vmin);
        printf("%d %d\n", vmax, vmin);
      }
      else {
        scanf("%d %d %d", &xql, &yql, &val);
        modifyX(1, 1, N, val, xql, yql);
      }
    }
  }
  return 0;
}