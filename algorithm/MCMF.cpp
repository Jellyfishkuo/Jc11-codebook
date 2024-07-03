#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
#define maxn 225
#define INF 0x3f3f3f3f
struct Edge
{
    int u, v, cap, flow, cost;
};
//node size, edge size, source, target
int n, m, s, t;
vector<vector<int>> G;
vector<Edge> edges;
//SPFA用
bool inqueue[maxn];
//SPFA用的dis[]
long long dis[maxn];
//maxFlow一路扣回去時要知道parent
//<注> 在這題因為G[][]中存的是edgeIndex in edges[]
//     所以parent存的也是對應edges[]中的edgeIndex(主要是方便)
int parent[maxn];
//maxFlow時需要紀錄到node u時的bottleneck
//同時也代表著u該次流出去的量
long long outFlow[maxn];
void addEdge(int u, int v, int cap, int cost)
{
    edges.emplace_back(Edge{u, v, cap, 0, cost});
    edges.emplace_back(Edge{v, u, 0, 0, -cost});
    m = edges.size();
    G[u].emplace_back(m - 2);
    G[v].emplace_back(m - 1);
}
//一邊求最短路的同時一邊MaxFLow
bool SPFA(long long& maxFlow, long long& minCost)
{
    // memset(outFlow, 0x3f, sizeof(outFlow));
    memset(dis, 0x3f, sizeof(dis));
    memset(inqueue, false, sizeof(inqueue));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inqueue[s] = true;
    outFlow[s] = INF;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        for (const int edgeIndex: G[u])
        {
            const Edge& edge = edges[edgeIndex];
            if ((edge.cap > edge.flow) && (dis[edge.v] > dis[u] + edge.cost))
            {
                dis[edge.v] = dis[u] + edge.cost;
                parent[edge.v] = edgeIndex;
                outFlow[edge.v] = min(outFlow[u], (long long)(edge.cap - edge.flow));
                if (!inqueue[edge.v])
                {
                    q.push(edge.v);
                    inqueue[edge.v] = true;
                }
            }
        }
    }
    //如果dis[t] > 0代表根本不賺還倒賠
    if (dis[t] > 0)
        return false;
    maxFlow += outFlow[t];
    minCost += dis[t] * outFlow[t];
    //一路更新回去這次最短路流完後要維護的MaxFlow演算法相關(如反向邊等)
    int curr = t;
    while (curr != s)
    {
        edges[parent[curr]].flow += outFlow[t];
        edges[parent[curr] ^ 1].flow -= outFlow[t];
        curr = edges[parent[curr]].u;
    }
    return true;
}
long long MCMF()
{
    long long maxFlow = 0;
    long long minCost = 0;
    while (SPFA(maxFlow, minCost))
        ;
    return minCost;
}
int main()
{
    int T;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; ++Case)
    {
        //總共幾個月，囤貨成本
        int M, I;
        scanf("%d %d", &M, &I);
        //node size
        n = M + M + 2;
        G.assign(n + 5, vector<int>());
        edges.clear();
        s = 0;
        t = M + M + 1;
        for (int i = 1; i <= M; ++i)
        {
            int produceCost, produceMax, sellPrice, sellMax, inventoryMonth;
            scanf("%d %d %d %d %d", &produceCost, &produceMax, &sellPrice, &sellMax, &inventoryMonth);
            addEdge(s, i, produceMax, produceCost);
            addEdge(M + i, t, sellMax, -sellPrice);
            for (int j = 0; j <= inventoryMonth; ++j)
            {
                if (i + j <= M)
                    addEdge(i, M + i + j, INF, I * j);
            }
        }
        printf("Case %d: %lld\n", Case, -MCMF());
    }
    return 0;
}