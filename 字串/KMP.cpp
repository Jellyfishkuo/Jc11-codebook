#define maxn 1000005
int nextArr[maxn];
void getNextArr(const string& s) {
  nextArr[0] = 0;
  int prefixLen = 0;
  for (int i = 1; i < s.size(); ++i) {
    prefixLen = nextArr[i - 1];
    //如果不一樣就在之前算過的prefix中
    //搜有沒有更短的前後綴
    while (prefixLen>0 && s[prefixLen]!=s[i])
      prefixLen = nextArr[prefixLen - 1];
    //一樣就繼承之前的前後綴長度+1
    if (s[prefixLen] == s[i])
      ++prefixLen;
    nextArr[i] = prefixLen;
  }
  for (int i = 0; i < s.size() - 1; ++i) {
    vis[nextArr[i]] = true;
  }
}