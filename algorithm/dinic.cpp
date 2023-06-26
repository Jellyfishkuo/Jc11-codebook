#include <stdio.h>
#include <string.h>
#include <queue>
#define MAXNODE 105
#define oo 1e9
using namespace std;

int nodeNum;
int graph[MAXNODE][MAXNODE];
int levelGraph[MAXNODE];
bool canReachSink[MAXNODE];

bool bfs(int from, int to){
    memset(levelGraph,0,sizeof(levelGraph));
    levelGraph[from]=1;
    queue<int> q;
    q.push(from);
    int currentNode;
    while(!q.empty()){
        currentNode=q.front();
        q.pop();
        for(int nextNode=1;nextNode<=nodeNum;++nextNode){
            if((levelGraph[nextNode]==0)&&
                graph[currentNode][nextNode]>0){
                levelGraph[nextNode]=levelGraph[currentNode]+1;
                q.push(nextNode);
            }
            if((nextNode==to)&&(graph[currentNode][nextNode]>0))
                return true;
        }
    }
    return false;
}
int dfs(int from, int to, int bottleNeck){
    if(from == to) return bottleNeck;
    int outFlow = 0;
    int flow;
    for(int nextNode=1;nextNode<=nodeNum;++nextNode){
        if((graph[from][nextNode]>0)&&
            (levelGraph[from]==levelGraph[nextNode]-1)&&
            canReachSink[nextNode]){
            flow=dfs(nextNode,to,min(graph[from][nextNode],bottleNeck));
            graph[from][nextNode]-=flow; //貪心
            graph[nextNode][from]+=flow; //反悔路
            outFlow+=flow;
            bottleNeck-=flow;
        }
        if(bottleNeck==0) break;
    }
    if(outFlow==0) canReachSink[from]=false;
    return outFlow;
}

int dinic(int from, int to){
    int maxFlow=0;
    while(bfs(from, to)){
        memset(canReachSink,1,sizeof(canReachSink));
        maxFlow += dfs(from, to, oo);
    }
    return maxFlow;
}

int main(){
    int from, to, edgeNum;
    int NetWorkNum = 1;
    int maxFlow;
    while(scanf("%d",&nodeNum)!=EOF&&nodeNum!=0){
        memset(graph, 0, sizeof(graph));
        scanf("%d %d %d", &from, &to, &edgeNum);
        int u, v, w;
        for (int i = 0; i < edgeNum; ++i){
            scanf("%d %d %d", &u, &v, &w);
            graph[u][v] += w;
            graph[v][u] += w;
        }
        maxFlow = dinic(from, to);
        printf("Network %d\n", NetWorkNum++);
        printf("The bandwidth is %d.\n\n", maxFlow);
    }
    return 0;
}