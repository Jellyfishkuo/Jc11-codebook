//倍增法預處理O(nlogn)，查詢O(logn)，
//利用lca找樹上任兩點距離
#define maxn 100005
struct Edge {
	int u, v, w;
};
vector<vector<Edge>> G; // tree
int fa[maxn][31]; //fa[u][i] -> u的第2^i個祖先
long long dis[maxn][31];
int dep[maxn];//深度
void dfs(int u, int p) {//預處理fa
    fa[u][0] = p; //因為u的第2^0 = 1的祖先就是p
    dep[u] = dep[p] + 1;
    //第2^i的祖先是(第2^(i - 1)個祖先)的
    //第2^(i - 1)的祖先
    //ex: 第8個祖先是 (第4個祖先)的第4個祖先
    for (int i = 1; i < 31; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        dis[u][i] = dis[fa[u][i - 1]][i - 1] + dis[u][i - 1];
    }
    //遍歷子節點
    for (Edge& edge: G[u]) {
        if (edge.v == p) 
            continue;
        dis[edge.v][0] = edge.w;
        dfs(edge.v, u);
    }
}
long long lca(int x, int y) {
    //此函數是找lca同時計算x、y的距離 -> dis(x, lca) + dis(lca, y)
    //讓y比x深
    if (dep[x] > dep[y])
        swap(x, y);
    int deltaDep = dep[y] - dep[x];
    long long res = 0;
    //讓y與x在同一個深度
    for (int i = 0; deltaDep != 0; ++i, deltaDep >>= 1)
        if (deltaDep & 1)
            res += dis[y][i], y = fa[y][i];
    if (y == x) //x = y -> x、y彼此是彼此的祖先
        return res;
    //往上找，一起跳，但x、y不能重疊
    for (int i = 30; i >= 0 && y != x; --i) {
        if (fa[x][i] != fa[y][i]) {
            res += dis[x][i] + dis[y][i];
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    //最後發現不能跳了，此時x的第2^0 = 1個祖先(或說y的第2^0 = 1的祖先)即為x、y的lca
    res += dis[x][0] + dis[y][0];
    return res;
}
int main() {
	int n, q;
	while (~scanf("%d", &n) && n) {
		int v, w;
		G.assign(n + 5, vector<Edge>());
        for (int i = 1; i <= n - 1; ++i) {
			scanf("%d %d", &v, &w);
			G[i + 1].push_back({i + 1, v + 1, w});
			G[v + 1].push_back({v + 1, i + 1, w});
		}
        dfs(1, 0);
        scanf("%d", &q);
        int u;
        while (q--) {
            scanf("%d %d", &u, &v);
            printf("%lld%c", lca(u + 1, v + 1), (q) ? ' ' : '\n');
        }
	}
	return 0;
}