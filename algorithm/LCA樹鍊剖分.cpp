#define maxn 5005
//LCA，用來練習樹鍊剖分
//題意: 給定樹，找任兩點的中點，
//若中點不存在(路徑為even)，就是中間的兩個點
int dfn[maxn];
int parent[maxn];
int depth[maxn];
int subtreeSize[maxn];
//樹鍊的頂點
int top[maxn];
//將dfn轉成node編碼
int dfnToNode[maxn];
//重兒子
int hson[maxn];
int dfsTime = 1;
//tree
vector<vector<int>> G;
//處理parent、depth、subtreeSize、dfnToNode
void dfs1(int u, int p) {
    parent[u] = p;
    hson[u] = -1;
    subtreeSize[u] = 1;
    for (int v: G[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs1(v, u);
            subtreeSize[u] += subtreeSize[v];
            if (hson[u] == -1 || subtreeSize[hson[u]] < subtreeSize[v]) {
                hson[u] = v;
            }
        }
    }
}
//實際剖分 <- 參數t是top的意思
//t初始應為root本身
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = dfsTime;
    dfnToNode[dfsTime] = u;
    ++dfsTime;
    //葉子點 -> 沒有重兒子
    if (hson[u] == -1)
        return;
    //優先對重兒子dfs，才能保證同一重鍊dfn連續
    dfs2(hson[u], t);
    for (int v: G[u]) {
        if (v != parent[u] && v != hson[u])
            dfs2(v, v);
    }
}
//不斷跳鍊，當跳到同一條鍊時，深度小的即為LCA
//跳鍊時優先鍊頂深度大的跳
int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = parent[top[u]];
        else
            v = parent[top[v]];
    }
    return (depth[u] > depth[v]) ? v : u;
}
int getK_parent(int u, int k) {
    while (k-- && (u != -1))
        u = parent[u];
    return u;
}
int main() {
    int n;
    while (scanf("%d", &n) && n) {
        dfsTime = 1;
        G.assign(n + 5, vector<int>());
        int u, v;
        for (int i = 1; i < n; ++i) {
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        dfs1(1, -1);
        dfs2(1, 1);
        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            scanf("%d %d", &u, &v);
            //先得到LCA
            int lca = LCA(u, v);
            //計算路徑長(經過的邊)
            int dis = depth[u] + depth[v] - 2 * depth[lca];
            //讓v比u深或等於
            if (depth[u] > depth[v])
                swap(u, v);
            if (u == v) {
                printf("The fleas meet at %d.\n", u);
            }
            else if (dis % 2 == 0) {
                //路徑長是even -> 有中點
                printf("The fleas meet at %d.\n", getK_parent(v, dis / 2));
            }
            else {
                //路徑長是odd -> 沒有中點
                if (depth[u] == depth[v]) {
                    int x = getK_parent(u, dis / 2);
                    int y = getK_parent(v, dis / 2);
                    if (x > y)
                        swap(x, y);
                    printf("The fleas jump forever between %d and %d.\n", x, y);
                }
                else {
                    //技巧: 讓深的點v往上dis / 2步 = y，
                    //這個點的parent設為x
                    //此時的x、y就是答案要的中點兩點
                    //主要是往下不好找，所以改用深的點用parent往上
                    int y = getK_parent(v, dis / 2);
                    int x = getK_parent(y, 1);
                    if (x > y)
                        swap(x, y);
                    printf("The fleas jump forever between %d and %d.\n", x, y);
                }
            }
        }
    }
    return 0;
}