//單純考SCC，每個SCC中找成本最小的蓋，如果有多個一樣小
//的要數出來，因為題目要方法數
//注意以下程式有縮點，但沒存起來，
//存法就是開一個array -> ID[u] = SCCID
#define maxn 100005
#define MOD 1000000007
long long cost[maxn];
vector<vector<int>> G;
int SCC = 0;
stack<int> sk;
int dfn[maxn];
int low[maxn];
bool inStack[maxn];
int dfsTime = 1;
long long totalCost = 0;
long long ways = 1;
void dfs(int u) {
  dfn[u] = low[u] = dfsTime;
  ++dfsTime;
  sk.push(u);
  inStack[u] = true;
  for (int v: G[u]) {
    if (dfn[v] == 0) {
        dfs(v);
        low[u] = min(low[u], low[v]);
    }
    else if (inStack[v]) {
        //屬於同個SCC且是我的back edge
        low[u] = min(low[u], dfn[v]);
    }
  }
  //如果是SCC
  if (dfn[u] == low[u]) {
    long long minCost = 0x3f3f3f3f;
    int currWays = 0;
    ++SCC;
    while (1) {
        int v = sk.top();
        inStack[v] = 0;
        sk.pop();
        if (minCost > cost[v]) {
            minCost = cost[v];
            currWays = 1;
        }
        else if (minCost == cost[v]) {
            ++currWays;
        }
        if (v == u) break;
    }
    totalCost += minCost;
    ways = (ways * currWays) % MOD;
  }
}