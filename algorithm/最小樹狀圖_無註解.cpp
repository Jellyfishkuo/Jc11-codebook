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
======================================================
O(m+nlog n)時間內解決最小樹形圖問題的演算法。
typedef long long ll;
#define maxn 102
#define INF 0x3f3f3f3f
struct UnionFind {
  int fa[maxn << 1];
  UnionFind() { memset(fa, 0, sizeof(fa)); }
  void clear(int n) { 
    memset(fa + 1, 0, sizeof(int) * n); 
  }
  int find(int x) { 
    return fa[x] ? fa[x] = find(fa[x]) : x; 
  }
  int operator[](int x) { return find(x); }
};
struct Edge {
  int u, v, w, w0;
};
struct Heap {
  Edge *e;
  int rk, constant;
  Heap *lch, *rch;
  Heap(Edge *_e):
    e(_e),rk(1),constant(0),lch(NULL),rch(NULL){}
  void push() {
    if (lch) lch->constant += constant;
    if (rch) rch->constant += constant;
    e->w += constant;
    constant = 0;
  }
};
Heap *merge(Heap *x, Heap *y) {
  if (!x) return y;
  if (!y) return x;
  if(x->e->w + x->constant > y->e->w + y->constant) 
    swap(x, y);
  x->push();
  x->rch = merge(x->rch, y);
  if (!x->lch || x->lch->rk < x->rch->rk) 
    swap(x->lch, x->rch);
  if (x->rch)
    x->rk = x->rch->rk + 1;
  else
    x->rk = 1;
  return x;
}
Edge *extract(Heap *&x) {
  Edge *r = x->e;
  x->push();
  x = merge(x->lch, x->rch);
  return r;
}
vector<Edge> in[maxn];
int n, m, fa[maxn << 1], nxt[maxn << 1];
Edge *ed[maxn << 1];
Heap *Q[maxn << 1];
UnionFind id;
void contract() {
  bool mark[maxn << 1];
  //將圖上的每一個節點與其相連的那些節點進行記錄
  for (int i = 1; i <= n; i++) {
    queue<Heap *> q;
    for (int j = 0; j < in[i].size(); j++) 
      q.push(new Heap(&in[i][j]));
    while (q.size() > 1) {
      Heap *u = q.front();
      q.pop();
      Heap *v = q.front();
      q.pop();
      q.push(merge(u, v));
    }
    Q[i] = q.front();
  }
  mark[1] = true;
  for(int a=1,b=1,p;Q[a];b=a,mark[b]=true){
    //尋找最小入邊以及其端點，保證無環
    do {
      ed[a] = extract(Q[a]);
      a = id[ed[a]->u];
    } while (a == b && Q[a]);
    if (a == b) break;
    if (!mark[a]) continue;
    //對發現的環進行收縮，以及環內的節點重新編號，
    //總權值更新
    for (a = b, n++; a != n; a = p) {
      id.fa[a] = fa[a] = n;
      if (Q[a]) Q[a]->constant -= ed[a]->w;
      Q[n] = merge(Q[n], Q[a]);
      p = id[ed[a]->u];
      nxt[p == n ? b : p] = a;
    }
  }
}
ll expand(int x, int r);
ll expand_iter(int x) {
  ll r = 0;
  for(int u=nxt[x];u!=x;u=nxt[u]){
    if (ed[u]->w0 >= INF)
      return INF;
    else
      r+=expand(ed[u]->v,u)+ed[u]->w0;
  }
  return r;
}
ll expand(int x, int t) {
  ll r = 0;
  for (; x != t; x = fa[x]) {
    r += expand_iter(x);
    if (r >= INF) return INF;
  }
  return r;
}
void link(int u, int v, int w) { 
  in[v].push_back({u, v, w, w}); 
}
int main() {
  int rt;
  scanf("%d %d %d", &n, &m, &rt);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    link(u, v, w);
  }
  //保證強連通
  for (int i = 1; i <= n; i++) 
    link(i > 1 ? i - 1 : n, i, INF);
  contract();
  ll ans = expand(rt, n);
  if (ans >= INF)
    puts("-1");
  else
    printf("%lld\n", ans);
  return 0;
}