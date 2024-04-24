const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;

struct Edge {
    int s, t, cap, flow;
};

int n, m, S, T;
int level[maxn], dfs_idx[maxn];
vector<Edge> E;
vector<vector<int>> G;

void init() {
    S = 0;
    T = n + m;
    E.clear();
    G.assign(maxn, vector<int>());
}

void addEdge(int s, int t, int cap) {
    E.push_back({s, t, cap, 0});
    E.push_back({t, s, 0, 0});
    G[s].push_back(E.size()-2);
    G[t].push_back(E.size()-1);
}

bool bfs() {
    queue<int> q({S});

    memset(level, -1, sizeof(level));
    level[S] = 0;

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for(int i : G[cur]) {
            Edge e = E[i];
            if(level[e.t]==-1 && e.cap>e.flow) {
                level[e.t] = level[e.s] + 1;
                q.push(e.t);
            }
        }
    }
    return ~level[T];
}

int dfs(int cur, int lim) {
    if(cur==T || lim==0) return lim;

    int result = 0;
    for(int& i=dfs_idx[cur]; i<G[cur].size() && lim; i++) {
        Edge& e = E[G[cur][i]];
        if(level[e.s]+1 != level[e.t]) continue;

        int flow = dfs(e.t, min(lim, e.cap-e.flow));
        if(flow <= 0) continue;

        e.flow += flow;
        result += flow;
        E[G[cur][i]^1].flow -= flow;
        lim -= flow;
    }
    return result;
}

int dinic() {       // O((V^2)E)
    int result = 0;
    while(bfs()) {
        memset(dfs_idx, 0, sizeof(dfs_idx));
        result += dfs(S, inf);
    }
    return result;
}