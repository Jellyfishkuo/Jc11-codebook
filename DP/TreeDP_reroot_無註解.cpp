/*re-root dp on tree O(n + n + n) -> O(n)*/
class Solution  {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges)  {
        this->res.assign(n, 0);
        G.assign(n + 5, vector<int>());
        for (vector<int>& edge: edges) {
            G[edge[0]].emplace_back(edge[1]);
            G[edge[1]].emplace_back(edge[0]);
        }
        memset(this->visited, 0, sizeof(this->visited));
        this->dfs(0);
        memset(this->visited, 0, sizeof(this->visited));
        this->res[0] = this->dfs2(0, 0);
        memset(this->visited, 0, sizeof(this->visited));
        this->dfs3(0, n);
        return this->res;
    }
private:
    vector<vector<int>> G;
    bool visited[30005];
    int subtreeSize[30005];
    vector<int> res;
    //求subtreeSize
    int dfs(int u) {
        this->visited[u] = true;
        for (int v: this->G[u])
            if (!this->visited[v])
                this->subtreeSize[u] += this->dfs(v);
        //自己
        this->subtreeSize[u] += 1;
        return this->subtreeSize[u];
    }
    //求res[0], 0到所有點的距離
    int dfs2(int u, int dis) {
        this->visited[u] = true;
        int sum = 0;
        for (int v: this->G[u])
            if (!visited[v])
                sum += this->dfs2(v, dis + 1);
        //要加上自己的距離
        return sum + dis;
    }
    //算出所有的res
    void dfs3(int u, int n) {
        this->visited[u] = true;
        for (int v: this->G[u]) {
            if (!visited[v]) {
                this->res[v] = this->res[u] + n - 2 * this->subtreeSize[v];
                this->dfs3(v, n);
            }
        }
    }
};