//計算閉區間 [1,n] 中有幾個正整數與 n 互質
// a^x = a^(x % phi(M) + phi(M)) mod M
int phi(){
    int ans=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    if(n>1) ans=ans-ans/n;
    return ans;

}
