/* 核心: 最大點獨立集 = |V| - |最大匹配數|，用匈牙利演算法找出最大匹配數 */
vector<Student> boys;
vector<Student> girls;
vector<vector<int>> G;
bool used[505];
int p[505];
bool match(int i) {
    for (int j: G[i]) {
        if (!used[j]) {
            used[j] = true;
            if (p[j] == -1 || match(p[j])) {
                p[j] = i;
                return true;
            }
        }
    }
    return false;
}
void maxMatch(int n) {
    memset(p, -1, sizeof(p));
    int res = 0;
    for (int i = 0; i < boys.size(); ++i) {
        memset(used, false, sizeof(used));
        if (match(i)) ++res;
    }
    cout << n - res << '\n';
}