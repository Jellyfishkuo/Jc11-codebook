//計算閉區間 [1,n] 中的正整數與 n 互質的個數
#include <bits/stdc++.h>
using namespace std;
int n,ans;

int phi(){
    ans=n;
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            ans=ans-ans/i;
            while(n%i==0) n/=i;
        }
    if(n>1) ans=ans-ans/n;
    return ans;
}

int main(){
	while(cin>>n)
    	cout<<phi()<<endl;
}