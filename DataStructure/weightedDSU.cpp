const int maxn = 2e5 + 10;

int p[maxn], val[maxn]; 

int findP(int x) {
    if(p[x] == -1) return x;
    int par = findP(p[x]);
    val[x] += val[p[x]];    //依題目更新val[x]
    return p[x] = par;
}

void merge(int u, int v, int w) {
    int pu = findP(u);
    int pv = findP(v);
    if(pu == pv) {
        // 理論上 val[v]-val[u] == w 
        // 依題目判斷 error 的條件
        return;
    }
    val[pv] = val[u] - val[v] + w;
    p[pv] = pu;
}