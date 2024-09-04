using ll = long long;
using mat = vector<vector<ll>>;
const int mod = 1e9 + 7;

mat operator*(mat A, mat B) {
  mat res(A.size(), vector<ll>(B[0].size()));
  for(int i=0; i<A.size(); i++) {
    for(int j=0; j<B[0].size(); j++) {
      for(int k=0; k<B.size(); k++) {
        res[i][j] += A[i][k] * B[k][j] % mod;
        res[i][j] %= mod;
      }
    }
  }
  return res;
}

mat I = ;
// compute matrix M^n
// 需先 init I 矩陣
mat mpow(mat& M, int n) {
  if(n <= 1) return n ? M : I;
  mat v = mpow(M, n>>1);
  return (n & 1) ? v*v*M : v*v;
}

// 迴圈版本
mat mpow(mat M, int n) {
  mat res(M.size(), vector<ll>(M[0].size()));
  for(int i=0; i<res.size(); i++)
    res[i][i] = 1;
  for(; n; n>>=1) {
    if(n & 1) res = res * M;
    M = M * M;
  }
  return res;
}