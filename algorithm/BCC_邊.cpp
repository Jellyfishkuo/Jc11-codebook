//oi-wiki，找無向圖的邊雙連通分量個數，
//並輸出每個邊雙連通分量
//對於任意u、v，刪去哪個邊都不會不連通 
//-> 邊雙連通(V + E)
constexpr int N = 5e5 + 5, M = 2e6 + 5;
int n, m, ans;
int tot = 1, hd[N];
struct edge {int to, nt;} e[M << 1];
void add(int u, int v) {e[++tot].to = v, e[tot].nt = hd[u], hd[u] = tot;}
void uadd(int u, int v) {add(u,v),add(v,u);}
bool bz[M << 1];
int bcc_cnt, dfn[N], low[N], vis_bcc[N];
vector<vector<int>> bcc;
void tarjan(int x, int in) {
  dfn[x] = low[x] = ++bcc_cnt;
  for (int i = hd[x]; i; i = e[i].nt) {
    int v = e[i].to;
    if (dfn[v] == 0) {
      tarjan(v, i);
      if (dfn[x] < low[v])
        bz[i] = bz[i ^ 1] = true;
      low[x] = min(low[x], low[v]);
    } else if (i != (in ^ 1))
      low[x] = min(low[x], dfn[v]);
  }
}
void dfs(int x, int id) {
  vis_bcc[x] = id, bcc[id - 1].push_back(x);
  for (int i = hd[x]; i; i = e[i].nt) {
    int v = e[i].to;
    if (vis_bcc[v] || bz[i]) continue;
    dfs(v, id);
  }
}