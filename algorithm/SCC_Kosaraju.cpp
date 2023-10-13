//做兩次dfs, O(V + E)
//g 是原圖，g2 是反圖
//s是dfs離開的節點
void dfs1(int u) {
    vis[u] = true;
    for (int v : g[u])
        if (!vis[v]) dfs1(v);
    s.push_back(u);
}

void dfs2(int u) {
    group[u] = sccCnt;
    for (int v : g2[u])
        if (!group[v]) dfs2(v);
}

void kosaraju() {
    sccCnt = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs1(i);
    for (int i = n; i >= 1; --i)
        if (!group[s[i]]) {
            ++sccCnt;
            dfs2(s[i]);
        }
}