#include <bits/stdc++.h>
#define word_maxn 4000*100+5
#define str_maxn 300000+5
#define sigma_num 26
#define MOD 20071027
using namespace std;

int dp[str_maxn];
char S[str_maxn];
char wd[100+5];

struct Trie{
    int ch[word_maxn][sigma_num];
    int val[word_maxn];
    int seq;
    void init(){
        seq=1;
        memset(ch,0,sizeof(ch));
    }
    void insertion(char *s){
        int row=0,n=strlen(s);
        for(int i=0;i<n;i++){
            int letter_no=s[i]-'a';
            if(ch[row][letter_no]==0){
                ch[row][letter_no]=seq;
                memset(ch[seq],0,sizeof(ch[seq]));
                val[seq++]=0;
            }
            row=ch[row][letter_no];
        }
        val[row]=n;
    }
    void find_prefix(char *s,int len,vector<int>&vc){
        int row=0;
        for(int i=0;i<len;i++){
            int letter_no=s[i]-'a';
            if(ch[row][letter_no]==0) return;
            row=ch[row][letter_no];
            if(val[row]) vc.push_back(val[row]);
        }
    }
}tr;

int main(){
    int Case=1;
    while(cin>>S){
        int n;
        cin>>n;
        tr.init();
        for(int i=0;i<n;i++){
            cin>>wd;
            tr.insertion(wd);
        }
        memset(dp,0,sizeof(dp));
        int N=strlen(S);
        dp[N]=1;
        for(int i=N-1;i>=0;i--){
            vector<int> vc;
            tr.find_prefix(S+i,N-i,vc);
            for(int j=0;j<vc.size();j++)
                dp[i]=(dp[i]+dp[i+vc[j]])%MOD;
        }
        cout<<"Case "<<Case++<<": "<<dp[0]<<endl;
    }
    return 0;
}

/*
 input
abcd
4
a b cd ab
 output
Case 1: 2
*/