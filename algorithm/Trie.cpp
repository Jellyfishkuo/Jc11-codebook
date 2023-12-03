#include <bits/stdc++.h>
using namespace std;

const int maxn = 300000 + 10;
const int mod = 20071027;

int dp[maxn];
int mp[4000*100 + 10][26];
char str[maxn];

struct Trie {
    int seq;
    int val[maxn];

    Trie() {
        seq = 0;
        memset(val, 0, sizeof(val));
        memset(mp, 0, sizeof(mp));
    }

    void insert(char* s, int len) {
        int r = 0;
        for(int i=0; i<len; i++) {
            int c = s[i] - 'a';
            if(!mp[r][c]) mp[r][c] = ++seq;
            r = mp[r][c];
        }
        val[r] = len;
        return;
    }

    int find(int idx, int len) {
        int result = 0;
        for(int r=0; idx<len; idx++) {
            int c = str[idx] - 'a';
            if(!(r = mp[r][c])) return result;
            if(val[r])
                result = (result + dp[idx + 1]) % mod;
        }
        return result;
    }
};

int main() {
    int n, tc = 1;

    while(~scanf("%s%d", str, &n)) {
        Trie tr;
        int len = strlen(str);
        char word[100+10];

        memset(dp, 0, sizeof(dp));
        dp[len] = 1;

        while(n--) {
            scanf("%s", word);
            tr.insert(word, strlen(word));
        }

        for(int i=len-1; i>=0; i--)
            dp[i] = tr.find(i, len);
        printf("Case %d: %d\n", tc++, dp[0]);
    }
    return 0;
}

/*************
 ****Input****
 * abcd
 * 4
 * a b cd ab
 *************
 ****Output***
 * Case 1: 2
 *************
*/