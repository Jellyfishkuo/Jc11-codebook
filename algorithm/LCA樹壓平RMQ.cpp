#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;
//樹壓平求LCA RMQ(sparse table O(nlogn)建立，O(1)查詢)，求任意兩點距離，
//如果用笛卡兒樹可以壓到O(n)建立，O(1)查詢
//理論上可以過，但遇到直鏈的case dfs深度會stack overflow
#define maxn 100005
struct Edge
{
	int u, v, w;
};
int dep[maxn];
int pos[maxn];
long long dis[maxn];
int st[maxn * 2][32]; //sparse table
int realLCA[maxn * 2][32]; //最小深度對應的節點，及真正的LCA
int Log[maxn]; //取代std::log2
int tp; // timestamp
vector<vector<Edge>> G; // tree
void calLog()
{
	Log[1] = 0;
	Log[2] = 1;
	for (int i = 3; i < maxn; ++i)
	{
		Log[i] = Log[i / 2] + 1;
	}
}
void buildST()
{
	for (int j = 0; Log[tp]; ++j)
	{
		for (int i = 0; i + (1 << j) - 1 < tp; ++i)
		{
			if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
			{
				st[i][j] = st[i - 1][j];
				realLCA[i][j] = realLCA[i - 1][j];
			}
			else
			{
				st[i][j] = st[i - 1][j + (1 << i - 1)];
				realLCA[i][j] = realLCA[i - 1][j + (1 << i - 1)];
			}
		}
	}
} // O(nlogn)
int query(int l, int r) // [l, r] min depth即為lca的深度
{
	int k = Log[r - l + 1];
	if (st[l][k] < st[r - (1 << k) + 1][k])
		return realLCA[l][k];
	else
		return realLCA[r - (1 << k) + 1][k];
}
void dfs(int u, int p) //euler tour
{
	pos[u] = tp;
	st[tp][0] = dep[u];
	realLCA[tp][0] = dep[u];
	++tp;
	for (int i = 0; i < G[u].size(); ++i)
	{
		Edge& edge = G[u][i];
		if (edge.v == p)
			continue;
		dep[edge.v] = dep[u] + 1;
		dis[edge.v] = dis[edge.u] + edge.w;
		dfs(edge.v, u);
		st[tp++][0] = dep[u];
	}
}
long long getDis(int u, int v)
{
	if (pos[u] > pos[v])
		swap(u, v);
	int lca = query(pos[u], pos[v]);
	return dis[u] + dis[v] - 2 * dis[query(pos[u], pos[v])];
}
int main()
{
	int n, q;
    calLog();
	while (~scanf("%d", &n) && n)
	{
		int v, w;
		G.assign(n + 5, vector<Edge>());
		tp = 0;
        for (int i = 1; i <= n - 1; ++i)
		{
			scanf("%d %d", &v, &w);
			G[i].push_back({i, v, w});
			G[v].push_back({v, i, w});
		}

        dfs(0, -1);
        buildST();

        scanf("%d", &q);
        int u;
        while (q--)
        {
            scanf("%d %d", &u, &v);
            printf("%lld%c", getDis(u, v), (q) ? ' ' : '\n');
        }
	}
	return 0;
}