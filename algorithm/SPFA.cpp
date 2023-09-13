struct Edge
{
    int t;
    long long w;
    Edge(){};
    Edge(int _t, long long _w) : t(_t), w(_w) {}
};

bool SPFA(int st) // 平均O(V + E) 最糟O(VE)
{
    vector<int> cnt(n, 0);
    bitset<MXV> inq(0);
    queue<int> q;
    q.push(st);
    dis[st] = 0;
    inq[st] = true;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for (auto &e : G[cur])
        {
            if (dis[e.t] <= dis[cur] + e.w)
                continue;
            dis[e.t] = dis[cur] + e.w;
            if (inq[e.t])
                continue;
            ++cnt[e.t];
            if (cnt[e.t] > n)
                return false; // negtive cycle
            inq[e.t] = true;
            q.push(e.t);
        }
    }
    return true;
}