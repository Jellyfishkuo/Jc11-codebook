void spfa(int s){
	for(int i=0;i<=n;i++) dis[i]=0x3f3f3f3f;
	dis[s]=0,vis[s]=1,q[1]=s;  
	int i,v,head=0,tail=1;
	while(head<tail){      //隊列非空
		head++; 
		v=q[head];         //取隊首元素
		vis[v]=0;   
		for(i=0;i<=n;i++)  //對所有頂點
		   if(a[v][i]>0&&dis[i]>dis[v]+a[v][i]){  
				dis[i]=dis[v]+a[v][i];//修改最短路
				if(vis[i]==0){
					tail++;
					q[tail]=i;
					vis[i]=1;
				}
		   }
		
	}
}