int w[n][n], d[n][n], p[n][n];	
// 由i點到j點的路徑，其中繼點為 p[i][j]。
void floyd_warshall(){ //O(V^3)
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			d[i][j]=w[i][j];
			p[i][j]=-1;	// 預設為沒有中繼點
		}
	for(int i=0;i<n;i++) d[i][i]=0;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(d[i][k]+d[k][j]<d[i][j]){
					d[i][j]=d[i][k]+d[k][j];
					p[i][j]=k; // 由i點走到j點經過了k點
				}
}
// 這支函式並不會印出起點和終點，必須另行印出。
void find_path(int s,int t){	// 印出最短路徑
	if(p[s][t]==-1) return;		// 沒有中繼點就結束
	find_path(s,p[s][t]);		// 前半段最短路徑
	cout<<p[s][t];				// 中繼點
	find_path(p[s][t],t);		// 後半段最短路徑
}
