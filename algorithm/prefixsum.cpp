// 前綴和
陣列前n項的和。
b[i]=a[0]+a[1]+a[2]+ … +a[i]
區間和 [l, r]：b[r]-b[l-1] (要保留b[l]所以-1)

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n],b[n];
    for(int i=0;i<n;i++) cin>>a[i];
    b[0]=a[0];
    for(int i=1;i<n;i++) b[i]=b[i-1]+a[i];
    for(int i=0;i<n;i++) cout<<b[i]<<' ';
    cout<<'\n';
    int l,r;
    cin>>l>>r;
    cout<<b[r]-b[l-1]; //區間和
}
