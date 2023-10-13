//Strongly Connected Components
//Tarjan O(V + E)
int dfn[N], low[N], dfncnt, sk[N], in_stack[N], tp;
//dfn[u]: dfs時u被visited的順序
//low[u]: 在u的dfs子樹中能回到最早已在stack中的節點  
int scc[N], sc;//節點 u 所在 SCC 的編號
int sz[N];//強連通 u 的大小

void tarjan(int u) {
    low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
    for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        ++sc;
        while (s[tp] != u) {
            scc[s[tp]] = sc;
            sz[sc]++;
            in_stack[s[tp]] = 0;
            --tp;
        }
        scc[s[tp]] = sc;
        sz[sc]++;
        in_stack[s[tp]] = 0;
        --tp;
    }
}