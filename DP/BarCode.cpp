int N, K, M;
long long dp[55][55];
// n -> 目前剩多少units
// k -> 目前剩多少bars
// m -> 1 bar最多多少units
long long dfs(int n, int k) {
    if (k == 1) {
        return (n <= M);
    }
    if (dp[n][k] != -1) 
        return dp[n][k];
    long long result = 0;
    for (int i = 1; i < min(M + 1, n); ++i) { // < min(M + 1, n)是因為n不能==0
        result += dfs(n - i, k - 1);
    }
    return dp[n][k] = result;
}
int main() {
    while (scanf("%d %d %d", &N, &K, &M) != EOF) {
        memset(dp, -1, sizeof(dp));
        printf("%lld\n", dfs(N, K));
    }
    return 0;
}