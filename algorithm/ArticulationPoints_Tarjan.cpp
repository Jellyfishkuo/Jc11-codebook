vector<vector<int>> G;
int N, timer;
bool visited[105];
int dfn[105]; // 第一次visit的時間
int low[105]; 
//最小能回到的父節點
//(不能是自己的parent)的visTime
int res;
//求割點數量
void tarjan(int u, int parent) {
  int child = 0;
  bool isCut = false;
  visited[u] = true;
  dfn[u] = low[u] = ++timer;
  for (int v: G[u]) {
    if (!visited[v]) {
      ++child;
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (parent != -1 && low[v] >= dfn[u])
        isCut = true;
    }
    else if (v != parent)
      low[u] = min(low[u], dfn[v]);
  }
//If u is root of DFS tree->有兩個以上的children
  if (parent == -1 && child >= 2)
    isCut = true;
  if (isCut) ++res;
}