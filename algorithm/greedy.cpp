//貪心
貪心演算法的核心為，
採取在目前狀態下最好或最佳（即最有利）的選擇。
貪心演算法雖然能獲得當前最佳解，
但不保證能獲得最後（全域）最佳解，
提出想法後可以先試圖尋找有沒有能推翻原本的想法的反例，
確認無誤再實作。


//problem
有一個 N×1 的稻田，有些稻田現在有種植作物，
為了避免被動物破壞，需要放置稻草人，
稻草人可以保護該塊稻田和左右兩塊稻田，
請問最少需要多少稻草人才能保護所有稻田?

//solutoin
從左到右掃描稻田，如果第 i 塊稻田有作物，
就把稻草人放到第 i+1 塊稻田，
這樣能保護第 i,i+1,i+2 塊稻田，
接著從第 i+3 塊稻田繼續掃描。

//code
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int i, n, t, tc = 1;
    cin >> t;
    while (t--){
        cin >> n >> s;
        int nc = 0;
        for (i = 0; i < n; i++)
            if (s[i] == '.')i += 2, nc++;
        cout << "Case " << tc++ << ": " << nc << endl;
    }
}


//problem
給定 N 個數，每次將兩個數 a,b 合併成 a+b，
只到最後只剩一個數，合併成本為兩數和，問最小合併成本為多少。

//solution
每次將最小的兩數合併起來。

//code
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, x;
    while (cin >> n, n)
    {
        priority_queue< int, vector<int>, greater<int> > q;
        while (n--)
        {
            cin >> x;
            q.push(x);
        }
        long long ans = 0;
        while (q.size() > 1)
        {
            x = q.top();
            q.pop();
            x += q.top();
            q.pop();
            q.push(x);
            ans += x;
        }
        cout << ans << endl;
    }
}


//problem
有 n 個部下，每個部下要花 Bi 分鐘交待任務，
再花 Ji 分鐘執行任務，一次只能對一位部下交代任務，
但可以多人同時執行任務，問最少要花多少時間完成任務。

//solution
執行時間長的人先交代任務

//code
#include <bits/stdc++.h>
using namespace std;
struct Data{
    int b, j;
    bool operator<(const Data &rhs) const {
        return j > rhs.j;
    }
};

int main(){
    int n, ti = 0;
    Data a[1005];
    while (cin >> n, n){
        for (int i = 0; i < n; ++i)
            cin >> a[i].b >> a[i].j;
        sort(a, a + n);
        int ans = 0, sum = 0;
        for (int i = 0; i < n; ++i){
            sum += a[i].b;
            ans = max(ans, sum + a[i].j);
        }
        cout << "Case " << ++ti << ": " << ans << '\n';
    }
}


//problem
給定一個數字 N(≤10^100)，需要刪除 K 個數字，
請問刪除 K 個數字後最小的數字為何?

//solution
刪除滿足第 i 位數大於第 i+1 位數的最左邊第 i 位數，
扣除高位數的影響較扣除低位數的大。

//code
int main()
{
    string s;
    int k;
    cin >> s >> k;
    for (int i = 0; i < k; ++i)
    {
        if ((int)s.size() == 0)
            break;
        int pos = (int)s.size() - 1;
        for (int j = 0; j < (int)s.size() - 1; ++j)
        {
            if (s[j] > s[j + 1])
            {
                pos = j;
                break;
            }
        }
        s.erase(pos, 1);
    }
    while ((int)s.size() > 0 && s[0] == '0')
        s.erase(0, 1);
    if ((int)s.size())
        cout << s << '\n';
    else
        cout << 0 << '\n';
}


區間覆蓋長度
//problem
給定 n 條線段區間為 [Li,Ri]，
請問這些線段的覆蓋所覆蓋的長度?

//solution
先將所有區間依照左界由小到大排序，
左界相同依照右界由小到大排序，
用一個變數 R 紀錄目前最大可以覆蓋到的右界。
如果目前區間左界 ≤R，代表該區間可以和前面的線段合併。

//code
struct Line
{
    int L, R;
    bool operator<(const Line &rhs) const
    {
        if (L != rhs.L)
            return L < rhs.L;
        return R < rhs.R;
    }
};

int main(){
    int n;
    Line a[10005];
    while (cin >> n){
        for (int i = 0; i < n; i++)
            cin >> a[i].L >> a[i].R;
        sort(a, a + n);
        int ans = 0, L = a[0].L, R = a[0].R;
        for (int i = 1; i < n; i++){
            if (a[i].L < R) R = max(R, a[i].R);
            else{
                ans += R - L;
                L = a[i].L;
                R = a[i].R;
            }
        }
        cout << ans + (R - L) << '\n';
    }
}

