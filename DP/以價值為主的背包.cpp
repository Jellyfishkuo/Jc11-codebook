/*w 變得太大所以一般的01背包解法變得不可能
  觀察題目w變成10^9
  而v_i變成10^3
  N不變10^2
  試著湊湊看dp狀態
  dp[maxn][maxv]是可接受的複雜度
  剩下的是轉移式，轉移式變成
  dp[i][j] = w -> 當目前只考慮到第i個商品時，達到獲利j時最少的weight總和 = w
  所以答案是dp[n][1 ~ maxv]找價值最大且裝的下的*/
#define maxn 105
#define maxv 100005
long long dp[maxn][maxv];
long long weight[maxn];
long long v[maxn];
int main() {
    int n;
    long long w;
    scanf("%d %lld", &n, &w);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &weight[i], &v[i]);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= maxv; ++j) {
            if (j - v[i] >= 0)
                dp[i][j] = dp[i - 1][j - v[i]] + weight[i];
            dp[i][j] = min(dp[i - 1][j], dp[i][j]);
        }
    }
    long long res = 0;
    for (int j = maxv - 1; j >= 0; --j) {
        if (dp[n][j] <= w) {
            res = j;
            break;
        }
    }
    printf("%lld\n", res);
    return 0;
}