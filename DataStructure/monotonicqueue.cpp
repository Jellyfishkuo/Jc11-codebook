//單調隊列
"如果一個選手比你小還比你強，你就可以退役了。"
example:
給出一個長度為 n 的數組，
輸出每 k 個連續的數中的最大值和最小值。
#define maxn 1000100
int q[maxn], a[maxn];
int n, k;
//得到這個隊列裡的最小值，直接找到最後的就行了
void getmin() {  
  int head=0, tail=0;
  for(int i=1;i<k;i++) {
    while(head<=tail&&a[q[tail]]>=a[i])tail--;
    q[++tail]=i;
  }
  for(int i=k; i<=n;i++) {
    while(head<=tail&&a[q[tail]]>=a[i])tail--;
    q[++tail]=i;
    while(q[head]<=i-k) head++;
    cout<<a[q[head]]<<" ";
  }
  cout<<endl;
}
// 和上面同理
void getmax() {  
  int head=0,tail=0;
  for(int i=1;i<k;i++) {
    while(head<=tail&&a[q[tail]]<=a[i])tail--;
    q[++tail]=i;
  }
  for(int i=k;i<=n;i++) {
    while(head<=tail&&a[q[tail]]<=a[i])tail--;
    q[++tail]=i;
    while(q[head]<=i-k) head++;
    cout<<a[q[head]]<<" ";
  }
  cout<<endl;
}