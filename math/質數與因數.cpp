質數

一般篩法 O(NloglogN) 
vector<int> p;
bitset<MAXN> is_notp;
void PrimeTable(int n)
{
    is_notp.reset();
    is_notp[0] = is_notp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (is_notp[i])
            continue;
        p.push_back(i);
        for (int j = i * i; j <= n; j += i)
        {
            is_notp[j] = 1;
        }
    }
}

線性篩法 O(N)
vector<int> p;
bitset<MAXN> is_notp;
void PrimeTable(int n)
{
    is_notp.reset();
    is_notp[0] = is_notp[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!is_notp[i])
            p.push_back(i);
        for (int j = 0; j < (int)p.size(); ++j)
        {
            if (i * p[j] > n)
                break;
            is_notp[i * p[j]] = 1;
            if (i % p[j] == 0)
                break;
        }
    }
}

因數

最大公因數 O(log(min(a,b))) 
int GCD(int a, int b)
{
    if (b == 0) return a;
    return GCD(b, a % b);
}

質因數分解

void primeFactorization(int n)
{
    for (int i = 0; i < (int)p.size(); ++i)
    {
        if (p[i] * p[i] > n)
            break;
        if (n % p[i])
            continue;
        cout << p[i] << ' ';
        while (n % p[i] == 0)
            n /= p[i];
    }
    if (n != 1)
        cout << n << ' ';
    cout << '\n';
}

歌德巴赫猜想
solution : 把偶數 N (6≤N≤10^6) 寫成兩個質數的和。
#include <iostream>
#include <cstdio>
using namespace std;
#define N 20000000
int ox[N], p[N], pr;

void PrimeTable(){
    ox[0] = ox[1] = 1;
    pr = 0;
    for (int i = 2; i < N; i++){
        if (!ox[i]) p[pr++] = i;
        for (int j = 0;i*p[j]<N&&j < pr; j++)
            ox[i*p[j]] = 1;
    }
}

int main(){
    PrimeTable();
    int n; 
        while (cin>>n,n){
            int x;
            for (x = 1;; x += 2)
                if (!ox[x] && !ox[n - x])break;
            printf("%d = %d + %d\n", n, x, n - x);
    }
}
problem : 給定整數 N，求 N 最少可以拆成多少個質數的和。
如果 N 是質數，則答案為 1。
如果 N 是偶數(不包含2)，則答案為 2 (強歌德巴赫猜想)。
如果 N 是奇數且 N−2 是質數，則答案為 2 (2+質數)。
其他狀況答案為 3 (弱歌德巴赫猜想)。
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, L, R) for(int i=L;i<(int)R;++i)
#define FORD(i, L, R) for(int i=L;i>(int)R;--i)
#define IOS                                                                    
    cin.tie(nullptr);                                                          
    cout.tie(nullptr);                                                         
    ios_base::sync_with_stdio(false);

bool isPrime(int n){
    FOR(i, 2, n){
        if (i * i > n)
            return true;
        if (n % i == 0)
            return false;
    }
    return true;
}

int main(){
    IOS;
    int n;
    cin >> n;
    if(isPrime(n)) cout << "1\n";
    else if(n%2==0||isPrime(n-2)) cout<<"2\n";
    else cout << "3\n";
}
