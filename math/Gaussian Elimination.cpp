using DBL = double;
using mat = vector<vector<DBL>>;

vector<DBL> Gauss(mat& M, int equ, int var) {
  auto dcmp = [](DBL a, DBL b=0.0) {
    return (a > b) - (a < b);
  };

  for(int r=0, c=0; r<equ && c<var; ) {
    int mx = r;   // 找絕對值最大的 M[i][c]
    for(int i=r+1; i<equ; i++) {
      if(dcmp(abs(M[i][c]),abs(M[mx][c]))==1)
        mx = i;
    }
    if(mx != r) swap(M[mx], M[r]);

    if(dcmp(M[r][c]) == 0) {
      c++;
      continue;
    }

    for(int i=r+1; i<equ; i++) {
      if(dcmp(M[i][c]) == 0) continue;
      DBL t = M[i][c] / M[r][c];
      for(int j=c; j<M[c].size(); j++) {
        M[i][j] -= t * M[r][j];
      }
    }
    r++, c++;
  }

  vector<DBL> X(var);
  for(int i=var-1; i>=0; i--) {
    X[i] = M[i][var];
    for(int j=var-1; j>i; j--) {
      X[i] -= M[i][j] * X[j];
    }
    X[i] /= M[i][i];
  }
  return X;
}