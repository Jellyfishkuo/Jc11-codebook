/*A*求k短路
  f(x) = g(x) + h(x)
  g(x) 是實際cost，h(x) 是估計cost
  在此h(x)用所有點到終點的最短距離，則當用Astar找點
  當該點cnt[u] == k時即得到該點的第k短路
*/
#define maxn 105
struct Edge { int u, v, w; };
struct Item_pqH {
    int u, w;
    bool operator <(const Item_pqH& other) const {
        return this->w > other.w;
    }
};
struct Item_astar {
    int u, g, f;
    bool operator <(const Item_astar& other) const {
        return this->f > other.f;
    }
};
vector<vector<Edge>> G;
//反向圖，用於建h(u)
vector<vector<Edge>> invertG;
int h[maxn];
bool visited[maxn];
int cnt[maxn];
//用反向圖去求出每一點到終點的最短距離，並以此當作h(u)
void dijkstra(int s, int t) {
    memset(visited, 0, sizeof(visited));
    priority_queue<Item_pqH> pq;
    pq.push({s, 0});
    h[s] = 0;
    while (!pq.empty()) {
        Item_pqH curr = pq.top();
        pq.pop();
        visited[curr.u] = true;
        for (Edge& edge: invertG[curr.u]) {
            if (!visited[edge.v]) {
                if (h[edge.v] > h[curr.u] + edge.w) {
                    h[edge.v] = h[curr.u] + edge.w;
                    pq.push({edge.v, h[edge.v]});
                }
            }
        }
    }
}
int Astar(int s, int t, int k) {
    memset(cnt, 0, sizeof(cnt));
    priority_queue<Item_astar> pq;
    pq.push({s, 0, h[s]});
    while (!pq.empty()) {
        Item_astar curr = pq.top();
        pq.pop();
        ++cnt[curr.u];
        //終點出現k次，此時即可得k短路
        if (cnt[t] == k)
            return curr.g;
        for (Edge& edge: G[curr.u]) {
            if (cnt[edge.v] < k) {
                pq.push({edge.v, curr.g + edge.w, curr.g + edge.w + h[edge.v]});
            }
        }
    }
    return -1;
}
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) && (n != 0 && m != 0)) {
        G.assign(n + 5, vector<Edge>());
        invertG.assign(n + 5, vector<Edge>());
        int s, t, k;
        scanf("%d %d %d", &s, &t, &k);
        int u, v, w;
        for (int i = 0; i < m; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            G[u].emplace_back(Edge{u, v, w});
            invertG[v].emplace_back(Edge{v, u, w});
        }
        memset(h, 0x3f, sizeof(h));
        dijkstra(t, s);
        printf("%d\n", Astar(s, t, k));
    }
    return 0;
}