//單調隊列
如果一個選手比你小還比你強，你就可以退役了。”--單調隊列

example 1

給出一個長度為 n 的數組，
編程輸出每 k 個連續的數中的最大值和最小值。
//寫法一
#include <bits/stdc++.h>
#define maxn 1000100
using namespace std;
int q[maxn], a[maxn];
int n, k;

void getmin() {  
  // 得到這個隊列裡的最小值，直接找到最後的就行了
  int head = 0, tail = 0;
  for (int i = 1; i < k; i++) {
    while (head <= tail && a[q[tail]] >= a[i]) tail--;
    q[++tail] = i;
  }
  for (int i = k; i <= n; i++) {
    while (head <= tail && a[q[tail]] >= a[i]) tail--;
    q[++tail] = i;
    while (q[head] <= i - k) head++;
    cout<<a[q[head]]<<" ";
  }
}

void getmax() {  // 和上面同理
  int head = 0, tail = 0;
  for (int i = 1; i < k; i++) {
    while (head <= tail && a[q[tail]] <= a[i]) tail--;
    q[++tail] = i;
  }
  for (int i = k; i <= n; i++) {
    while (head <= tail && a[q[tail]] <= a[i]) tail--;
    q[++tail] = i;
    while (q[head] <= i - k) head++;
    cout<<a[q[head]]<<" ";
  }
}

int main() {
  cin>>n>>k;  //每k個連續的數 
  for (int i = 1; i <= n; i++) cin>>a[i];
  getmin();
  cout<<'\n';
  getmax();
  cout<<'\n';
  return 0;
}

//寫法2
#include <iostream>
#include <cstring>
#include <deque>
using namespace std;
int a[1000005];
 
int main() {
    ios_base::sync_with_stdio(0);
    int n, k;
    while(cin>>n>>k) {
        for(int i=0; i<n; i++) cin >> a[i];
        deque<int> dq;
        for(int i=0; i<n; i++){
            while(dq.size() && dq.front()<=i-k)
                dq.pop_front();
            while(dq.size() && a[dq.back()]>a[i]) 
                dq.pop_back();
            dq.push_back(i);
            if(i==k-1) cout<<a[dq.front()];
            if(i>k-1) cout<<' '<<a[dq.front()];
        }
        if(k>n) cout<<a[dq.front()];
        cout<<'\n';
        while(dq.size()) dq.pop_back();
        for(int i=0; i<n; i++){
            while(dq.size() && dq.front()<=i-k)
                dq.pop_front();
            while(dq.size() && a[dq.back()]<a[i]) 
                dq.pop_back();
            dq.push_back(i);
            if(i==k-1) cout<<a[dq.front()];
            if(i>k-1)  cout<<' '<<a[dq.front()];
        }
        if(k>n) cout<<a[dq.front()];
        cout<<'\n';
    }
    return 0;
}


example 2

一個含有 n 項的數列，求出每一項前的 m 個數到它這個區間內的最小值。
若前面的數不足 m 項則從第 1 個數開始，若前面沒有數則輸出 0 

#include<bits/stdc++.h>
using namespace std;
#define re register int
#define INF 0x3f3f3f3f
#define ll long long
#define maxn 2000009
#define maxm
inline ll read() {
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ll)(ch-'0');
		ch=getchar();
	}
    return x*f;
}
int n,m,k,tot,head,tail;
int a[maxn],q[maxn];
int main() {
    n=read(), m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    head=1,tail=0;//起始位置為1 因為插入是q[++tail]所以要初始化為0
    for(int i=1;i<=n;i++)//每次隊首的元素就是當前的答案 
    {
        cout<<a[q[head]]<<endl;
        while(i-q[head]+1>m&&head<=tail)//維護隊首 
            head++;
        while(a[i]<a[q[tail]]&&head<=tail)//維護隊尾 
            tail--;
        q[++tail]=i;
    }
    return 0;
}