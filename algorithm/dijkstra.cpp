#include<bits/stdc++.h>
#define maxn 50000+5
#define INF 0x3f3f3f3f
using namespace std;

struct edge{
    int v,w;
};

struct Item{
    int u,dis;
    bool operator<(const Item &rhs)const{
        return dis>rhs.dis;
    }
};

vector<edge> G[maxn];
int dist[maxn];

void dijkstra(int s){ // O((V + E)logE)
    memset(dist,INF,sizeof(dist));
    dist[s]=0;
    priority_queue<Item> pq;
    pq.push({s,0});
    while(!pq.empty()){
        Item now=pq.top();
        pq.pop();
        if(now.dis>dist[now.u]) continue;
        for(edge e:G[now.u]){
            if(dist[e.v]>dist[now.u]+e.w){
                dist[e.v]=dist[now.u]+e.w;
                pq.push({e.v,dist[e.v]});
            }
        }
    }
}

int main(){
    int t,cas=1;
    cin>>t;
    while(t--){
        int n,m,s,t;
        cin>>n>>m>>s>>t;
        for(int i=0;i<=n;i++) G[i].clear();
        int u,v,w;
        for(int i=0;i<m;i++){
            cin>>u>>v>>w;
            G[u].push_back({v,w});
            G[v].push_back({u,w});
        }
        dijkstra(s);
        cout<<"Case #"<<cas++<<": ";
        if(dist[t]==INF) cout<<"unreachable\n";
        else cout<<dist[t]<<endl;
    }
}