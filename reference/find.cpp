#include<bits/stdc++.h>
using namespace std;

int arr[10000];

int main(){
    string s,a,b;
    int cnt=0;
    while(getline(cin,s)){
        if(cnt++) cout<<endl;
        cin>>a>>ws>>b;
        int pos=0,i=0,r=0;
        memset(arr,0,sizeof(arr));
        while(1){
            pos=s.find(a,pos);
            if(pos==-1) break;
            arr[i++]=pos-r;
            r+=b.size()-a.size();
            s.replace(pos,a.length(),b);
            pos+=b.length();
        }
        if(i)
            for(int j=0;j<i;j++){
                if(j) cout<<" ";
                cout<<arr[j];
            }
        else cout<<-1;
        cout<<endl<<s<<endl;
        cin>>ws;
    }
    return 0;
}