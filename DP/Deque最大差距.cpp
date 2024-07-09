/*定義dp[l][r]是l ~ r時與先手最大差異值
  轉移式：dp[l][r] = max{a[l] - solve(l + 1, r), a[r] - solve(l, r - 1)}
  裡面用減的主要是因為求的是相減且會一直換手，
  所以正負正負...*/
#define maxn 3005
bool vis[maxn][maxn];
long long dp[maxn][maxn];
long long a[maxn];
long long solve(int l, int r) {
    if (l > r) return 0;
    if (vis[l][r]) return dp[l][r];
    vis[l][r] = true;
    long long res = a[l] - solve(l + 1, r);
    res = max(res, a[r] - solve(l, r - 1));
    return dp[l][r] = res;
}
int main() {
    ...
    printf("%lld\n", solve(1, n));
}