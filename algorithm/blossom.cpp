const int maxn = 500 + 10;

struct Edge { int s, t; };

int n;
int base[maxn],match[maxn],p[maxn],inq[maxn];
bool vis[maxn], flower[maxn];
vector<Edge> G[maxn];
queue<int> q;

int lca(int a, int b) {
  memset(vis, 0, sizeof(vis));
  while(1) {
    a = base[a];
    vis[a] = true;
    if(match[a] == -1) break;
    a = p[match[a]];
  }
  while(1) {
    b = base[b];
    if(vis[b]) return b;
    b = p[match[b]];
  }
  return -1;
}

void set_path(int x, int father) {
  int tmp;
  while(x != father) {
    tmp = match[x];
    flower[base[x]]=flower[base[tmp]]=1;
    tmp = p[tmp];
    if(base[tmp]!=father) p[tmp] = match[x];
    x = tmp;
  }
}

void blossom(int x, int y) {
  memset(flower, 0, sizeof(flower));
  int father = lca(x, y);
  set_path(x, father);
  set_path(y, father);
  if(base[x] != father) p[x] = y;
  if(base[y] != father) p[y] = x;
  for(int i=1; i<=n; i++) {
    if(!flower[base[i]]) continue;
    base[i] = father;
    if(!inq[i]) {
      q.push(i);
      inq[i] = true;
    }
  }
}

bool bfs(int root) {
  int cur, y, nxt;
  q = queue<int>();
  q.push(root); 
  memset(inq, 0, sizeof(inq));
  memset(p, -1, sizeof(p));
  for(int i=1; i<=n; i++) base[i] = i;

  while(!q.empty()) {
    cur = q.front();
    q.pop();
    inq[cur] = false;

    for(auto e : G[cur]) {
      if(base[e.s] == base[e.t]) continue;
      if(match[e.s] == e.t) continue;
      if(e.t == root ||
        (~match[e.t] && ~p[match[e.t]])) {
        blossom(cur, e.t);
      } else if(p[e.t] == -1) {
        p[e.t] = cur;
        if(match[e.t] == -1) {
          cur = e.t;
          while(cur != -1) {
            y = p[cur];
            nxt = match[y];
            match[cur] = y;
            match[y] = cur;
            cur = nxt;
          }
          return true;
        } else {
          q.push(match[e.t]);
          inq[match[e.t]] = true;
        }
      }
    }
  }
  return false;
}

int maxMatch() {
  int res = 0;
  memset(match, -1, sizeof(match));
  for(int i=1; i<=n; i++) {
    if(match[i]==-1 && bfs(i)) res++;
  }
  return res;
}