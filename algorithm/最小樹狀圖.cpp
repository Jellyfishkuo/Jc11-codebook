  定義
有向圖上的最小生成樹（Directed Minimum Spanning Tree）
稱為最小樹形圖。
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
  Tarjan 的DMST 演算法
Tarjan 提出了一種能夠在
O(m+nlog n)時間內解決最小樹形圖問題的演算法。
  流程
Tarjan 的演算法分為收縮與伸展兩個過程。
接下來先介紹收縮的過程。
我們要假設輸入的圖是滿足強連通的，
如果不滿足那就加入 O(n) 條邊使其滿足，
並且這些邊的邊權是無窮大的。
我們需要一個堆存儲結點的入邊編號，入邊權值，
結點總代價等相關信息，由於後續過程中會有堆的合併操作，
這裡採用左偏樹 與並查集實現。
演算法的每一步都選擇一個任意結點v，
需要保證v不是根節點，並且在堆中沒有它的入邊。
再將v的最小入邊加入到堆中，
如果新加入的這條邊使堆中的邊形成了環，
那麼將構成環的那些結點收縮，
我們不妨將這些已經收縮的結點命名為超級結點，
再繼續這個過程，如果所有的頂點都縮成了超級結點，
那麼收縮過程就結束了。
整個收縮過程結束後會得到一棵收縮樹，
之後就會對它進行伸展操作。
堆中的邊總是會形成一條路徑v0 <- v1<- ... <- vk，
由於圖是強連通的，這個路徑必然存在，
並且其中的 vi 可能是最初的單一結點，
也可能是壓縮後的超級結點。
最初有 v0=a，其中 a 是圖中任意的一個結點，
每次都選擇一條最小入邊 vk <- u，
如果 u 不是v0,v1,...,vk中的一個結點，
那麼就將結點擴展到 v k+1=u。
如果 u 是他們其中的一個結點 vi，
那麼就找到了一個關於 vi <- ... <- vk <- vi的環，
再將他們收縮為一個超級結點c。
向隊列 P 中放入所有的結點或超級結點，
並初始選擇任一節點 a，只要佇列不為空，就進行以下步驟：
選擇 a 的最小入邊，保證不存在自環，
並找到另一頭的結點 b。
如果結點b沒有被記錄過說明未形成環，
令 a <- b，繼續目前操作尋找環。
如果 b 被記錄過了，就表示出現了環。
總結點數加一，並將環上的所有結點重新編號，對堆進行合併，
以及結點/超級結點的總權值的更新。
更新權值操作就是將環上所有結點的入邊都收集起來，
並減去環上入邊的邊權。
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