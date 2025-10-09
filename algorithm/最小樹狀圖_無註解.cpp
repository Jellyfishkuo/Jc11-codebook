const int maxn = 60 + 10;
const int inf = 0x3f3f3f3f;
struct Edge {
  int s, t, cap, cost;
}; // cap 為頻寬 (optional)
int n, m, c;
int inEdge[maxn], idx[maxn], pre[maxn], vis[maxn];
// 對於每個點，選擇對它入度最小的那條邊
// 找環，如果沒有則 return;
// 進行縮環並更新其他點到環的距離。
int dirMST(vector<Edge> edges, int low) {
  int result = 0, root = 0, N = n;
  while(true) {
    memset(inEdge, 0x3f, sizeof(inEdge));
    // 找所有點的 in edge 放進 inEdge
    // optional: low 為最小 cap 限制
    for(const Edge& e : edges) {
      if(e.cap < low) continue;
      if(e.s!=e.t && e.cost<inEdge[e.t]) {
        inEdge[e.t] = e.cost;
        pre[e.t] = e.s;
      }
    }
    for(int i=0; i<N; i++) {
      if(i!=root && inEdge[i]==inf)
        return -1;//除了root 還有點沒有in edge
    }
    int seq = inEdge[root] = 0;
    memset(idx, -1, sizeof(idx));
    memset(vis, -1, sizeof(vis));
    // 找所有的 cycle，一起編號為 seq
    for(int i=0; i<N; i++) {
      result += inEdge[i];
      int cur = i;
      while(vis[cur]!=i && idx[cur]==-1) {
        if(cur == root) break;
        vis[cur] = i;
        cur = pre[cur];
      }
      if(cur!=root && idx[cur]==-1) {
        for(int j=pre[cur]; j!=cur; j=pre[j])
          idx[j] = seq;
        idx[cur] = seq++;
      }
    }
    if(seq == 0) return result; // 沒有 cycle
    for(int i=0; i<N; i++)
      // 沒有被縮點的點
      if(idx[i] == -1) idx[i] = seq++;
    // 縮點並重新編號
    for(Edge& e : edges) {
      if(idx[e.s] != idx[e.t])
        e.cost -= inEdge[e.t];
      e.s = idx[e.s];
      e.t = idx[e.t];
    }
    N = seq;
    root = idx[root];
  }
}