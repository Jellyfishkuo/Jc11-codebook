// 前綴和
// 陣列前n項的和。
// b[i] = a[0] + a[1] + a[2] + … + a[i]
// 區間和 [l, r]：b[r]-b[l-1] (要保留b[l]所以-1)

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int a[n], b[n];
    for(int i=0; i<n; i++) cin >> a[i];
    b[0] = a[0];
    for(int i=1; i<n; i++) b[i] = b[i-1] + a[i];
    for(int i=0;i<n;i++) cout<<b[i]<<' ';
    cout<<'\n';
    int l, r;
    cin >> l >> r;
    cout << b[r] - b[l-1] ; //區間和
}


// 差分
// 用途：在區間 [l, r] 加上一個數字v。
// b[l] += v; (b[0~l] 加上v)
// b[r+1] -= v; (b[r+1~n] 減去v (b[r] 仍保留v) )
// 給的 a[] 是前綴和數列，建構 b[]，
// 因為 a[i] = b[0] + b[1] + b[2] + … + b[i]，
// 所以 b[i] = a[i] – a[i-1]。
// 在 b[l] 加上 v，b[r+1] 減去 v，
// 最後再從 0 跑到 n 使 b[i] += b[i-1]。
// 這樣一來，b[] 是一個在某區間加上v的前綴和。

#include <bits/stdc++.h>
using namespace std;
int a[1000], b[1000];
//a: 前綴和數列, b: 差分數列
int main(){
    int n, l, r, v;
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> a[i];
        b[i] = a[i] - a[i-1]; //建構差分數列
    }
    cin >> l >> r >> v;
    b[l] += v;
    b[r+1] -= v;
    
    for(int i=1; i<=n; i++){
        b[i] += b[i-1];
        cout << b[i] << ' ';
    }
}