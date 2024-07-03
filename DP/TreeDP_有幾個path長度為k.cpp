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
    //統計橫跨u但還是在u的子樹中合計長度為k的:
    //考慮u有一子節點v，在v子樹中距離v長度為x的
    //以及不在v子樹但在u子樹中(這樣才會是橫跨u)且距離u長度為k - x - 1的
    //共有0.5 * (dp[v][x] * (dp[u][k - x - 1] - dp[v][k - x - 2]))
    //以上算式是重點，可使複雜度下降，否則枚舉一定超時
    //其中 dp[u][k - x - 1]是所有u子樹中距離u為k - x - 1的節點
    // - dp[v][k - x - 2]是因為我們不要v子樹的節點且距離u為k - x - 1的(要v子樹以外的)，
    //那些點有dp[v][k - x - 2]，最後0.5是由於計算中i -> j以及j -> i(i、j是不同節點)
    //都會被算一遍，所以要 * 0.5
    long long cnt = 0;
    for (int v: G[u]) {
        if (v == p)
            continue;
        for (int x = 0; x <= k - 2; ++x) {
            cnt += dp[v][x] * (dp[u][k - x - 1] - dp[v][k - x - 2]);
        }
    }
    res += cnt / 2;
}
int main() {
    scanf("%d %d", &n, &k);
    G.assign(n + 5, vector<int>());
    int u, v;
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &u, &v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(1, -1);
    printf("%lld\n", res);
    return 0;
}