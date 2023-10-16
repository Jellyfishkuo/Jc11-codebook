  題意
給定 B,N,P，求出 L 滿足 B^L≡N(mod P)。

\begin{itemize}
$\sum \limits_{i=1}^n i^2 = \frac{n(n+1)(2n+1)}{6}$
\end{itemize}


$\sum \limits_{i=1}^n i^2 = \frac{n(n+1)(2n+1)}{6}$


  題解
餘數的循環節長度必定為 P 的因數，因此 B^0≡B^P,B^1≡B^(P+1),…，
也就是說如果有解則 L<N，枚舉0,1,2,L−1 能得到結果，但會超時。

將 L 拆成 mx+y，只要分別枚舉 x,y 就能得到答案，
設 m=√P 能保證最多枚舉 2√P 次 。

B^(mx+y)≡N(mod P) 
B^(mx)B^y≡N(mod P)
B^y≡N(B^(−m))^x (mod P)

先求出 B^0,B^1,B^2,...,B^(m−1)，
再枚舉 N(B^(−m)),N(B^(−m))^2,… 查看是否有對應的 B^y。
這種算法稱為大步小步演算法，
大步指的是枚舉 x (一次跨 m 步)，
小步指的是枚舉 y (一次跨 1 步)。

  複雜度分析
利用 map/unorder_map 存放 B^0,B^1,B^2,…,B^(m−1)，
枚舉 x 查詢 map/unorder_map 是否有對應的 B^y，
存放和查詢最多 2√P 次，時間複雜度為 O(√Plog√P)/O(√P)。



#include <bits/stdc++.h>
using namespace std;
using LL = long long;
LL B, N, P;

LL fpow(LL a,LL b,LL c){
    LL res=1;
    for(;b;b >>=1){
        if(b&1)
            res=(res*a)%c;
        a=(a*a)%c;
    }
    return res;
}

LL BSGS(LL a,LL b,LL p){
    a%=p,b%=p;
    if(a==0)
        return b==0?1:-1;
    if(b==1)
        return 0;
    map<LL, LL> tb;
    LL sq=ceil(sqrt(p-1));
    LL inv=fpow(a,p-sq-1,p);
    tb[1]=sq;
    for(LL i=1,tmp=1;i<sq;++i){
        tmp=(tmp*a)%p;
        if(!tb.count(tmp))
            tb[tmp]=i;
    }
    for(LL i=0;i<sq;++i){
        if(tb.count(b)){
            LL res=tb[b];
            return i*sq+(res==sq?0:res);
        }
        b=(b*inv)%p;
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    while(cin>>P>>B>>N){
        LL ans=BSGS(B,N,P);
        if(ans==-1)
            cout<<"no solution\n";
        else
            cout<<ans<<'\n';
    }
}
