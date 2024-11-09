const int maxn = 1e4 + 10;  // 單字字數
const int maxl = 50 + 10;   // 單字字長
const int maxc = 128;       // 單字字符數
const char minc = ' ';      // 首個 ASCII

int trie[maxn*maxl][maxc];  // 原字典樹
int val[maxn*maxl];         // 結尾(單字編號)
int cnt[maxn*maxl];         // 結尾(重複個數)
int fail[maxn*maxl];        // failure link
bool vis[maxn*maxl];        // 同單字不重複

struct ACTrie {
  int seq, root;

  ACTrie() {
    seq = 0;
    root = newNode();
  }

  int newNode() {
    for(int i=0; i<maxc; i++) trie[seq][i]=0;
    val[seq] = cnt[seq] = fail[seq] = 0;
    return seq++;
  }

  void insert(char* s, int wordId=0) {
    int p = root;
    for(; *s; s++) {
      int c = *s - minc;
      if(!trie[p][c]) trie[p][c] = newNode();
      p = trie[p][c];
    }
    val[p] = wordId;
    cnt[p]++;
  }

  void build() {
    queue<int> q({root});
    while(!q.empty()) {
      int p = q.front();
      q.pop();
      for(int i=0; i<maxc; i++) {
        int& t = trie[p][i];
        if(t) {
          fail[t] = p?trie[fail[p]][i]:root;
          q.push(t);
        } else {
          t = trie[fail[p]][i];
        }
      }
    }
  }

  // 要存 wordId 才要 vec
  // 同單字重複match要把所有vis取消掉
  int match(char* s, vector<int>& vec) {
    int res = 0;
    memset(vis, 0, sizeof(vis));
    for(int p=root; *s; s++) {
      p = trie[p][*s-minc];
      for(int k=p; k && !vis[k]; k=fail[k]) {
        vis[k] = true;
        res += cnt[k];
        if(cnt[k]) vec.push_back(val[k]);
      }
    }
    return res;     // 匹配到的單字量
  }
};

ACTrie ac;      // 建構，初始化
ac.insert(s);   // 加字典單字
// 加完字典後
ac.build();     // !!! 建 failure link !!!
ac.match(s);    // 多模式匹配(傳入vec可以存編號)