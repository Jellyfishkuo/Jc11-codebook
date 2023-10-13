#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> G;
int N;
int timer;
bool visited[105];
int visTime[105]; // 第一次visit的時間
int low[105]; // 最小能回到的父節點(不能是自己的parent)的visTime
int res;
//求割點數量
void tarjan(int u, int parent) {
    int child = 0;
    bool isCut = false;
    visited[u] = true;
    visTime[u] = low[u] = ++timer;
    for (int v: G[u]) {
        if (!visited[v]) {
            ++child;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (parent != -1 && low[v] >= visTime[u])
                isCut = true;
        }
        else if (v != parent)
            low[u] = min(low[u], visTime[v]);
    }
    //If u is root of DFS tree->有兩個以上的children
    if (parent == -1 && child >= 2)
        isCut = true;
    if (isCut)
        ++res;
}

int main()
{
    char input[105];
    char* token;
    while (scanf("%d", &N) != EOF && N)
    {
        G.assign(105, vector<int>());
        memset(visited, false, sizeof(visited));
        memset(low, 0, sizeof(low));
        memset(visTime, 0, sizeof(visited));
        timer = 0;
        res = 0;
        getchar(); // for \n
        while (fgets(input, 105, stdin))
        {
            if (input[0] == '0')
                break;
            int size = strlen(input);
            input[size - 1] = '\0';
            --size;
            token = strtok(input, " ");
            int u = atoi(token);
            int v;
            while (token = strtok(NULL, " "))
            {
                v = atoi(token);
                G[u].emplace_back(v);
                G[v].emplace_back(u);
            }
        }
        tarjan(1, -1);
        printf("%d\n", res);
    }
    return 0;
}