#define maxn 50005
#define maxk 505
//dp[u][u的child且距離u長度k的數量]
long long dp[maxn][maxk];
vector<vector<int>> G;
int n, k;
long long res = 0;
void dfs(int u, int p) {
    //u自己
    dp[u][0] = 1;
    for (int v: G[u]) {
        if (v == p)
            continue;
        dfs(v, u);
        for (int i = 1; i <= k; ++i) {
            //子樹v距離i - 1的等於對於u來說距離i的
            dp[u][i] += dp[v][i - 1];
        }
    }
    //統計在u子樹中距離u為k的數量
    res += dp[u][k];
    long long cnt = 0;
    for (int v: G[u]) {
        if (v == p)
            continue; //重點算法
        for (int x = 0; x <= k - 2; ++x) {
            cnt += dp[v][x] * (dp[u][k - x - 1] - dp[v][k - x - 2]);
        }
    }
    res += cnt / 2;
}
int main() {
    ...
    dfs(1, -1);
    printf("%lld\n", res);
    return 0;
}