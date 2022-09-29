//貪心
貪心演算法的核心為，
採取在目前狀態下最好或最佳（即最有利）的選擇。
貪心演算法雖然能獲得當前最佳解，
但不保證能獲得最後（全域）最佳解，
提出想法後可以先試圖尋找有沒有能推翻原本的想法的反例，
確認無誤再實作。

Scarecrow
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
        cout<<"Case "<<tc++<<": "<<nc<<endl;
    }
}

霍夫曼樹的變形題
//problem
給定 N 個數，每次將兩個數 a,b 合併成 a+b，
只到最後只剩一個數，合併成本為兩數和，
問最小合併成本為多少。

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
        priority_queue<int,vector<int>,greater<int>> q;
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

Commando War
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
        cout<<"Case "<<++ti<<": "<<ans<<'\n';
    }
}

刪數字問題
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


最小區間覆蓋長度
//problem
給定 n 條線段區間為 [Li,Ri]，
請問最少要選幾個區間才能完全覆蓋 [0,S]?

//solution
先將所有區間依照左界由小到大排序，
對於當前區間 [Li,Ri]，要從左界 >Ri 的所有區間中，
找到有著最大的右界的區間，連接當前區間。

//problem
長度 n 的直線中有數個加熱器，
在 x 的加熱器可以讓 [x−r,x+r] 內的物品加熱，
問最少要幾個加熱器可以把 [0,n] 的範圍加熱。

//solution
對於最左邊沒加熱的點a，選擇最遠可以加熱a的加熱器，
更新已加熱範圍，重複上述動作繼續尋找加熱器。

//code
int main(){
    int n, r;
    int a[1005];
    cin >> n >> r;
    for (int i=1;i<=n;++i) cin>>a[i];
    int i = 1, ans = 0;
    while (i <= n){
        int R=min(i+r-1, n), L=max(i-r+1, 0)
        int nextR=-1;
        for (int j = R; j >= L; --j){
            if (a[j]){
                nextR = j;
                break;
            }
        }
        if (nextR == -1){
            ans = -1;
            break;
        }
        ++ans;
        i = nextR + r;
    }
    cout << ans << '\n';
}


最多不重疊區間
//problem
給你 n 條線段區間為 [Li,Ri]，
請問最多可以選擇幾條不重疊的線段(頭尾可相連)?

//solution
依照右界由小到大排序，
每次取到一個不重疊的線段，答案 +1。

//code
struct Line
{
    int L, R;
    bool operator<(const Line &rhs) const {
         return R < rhs.R; 
        }
};

int main()
{
    int t;
    cin >> t;
    Line a[30];
    while (t--)
    {
        int n = 0;
        while (cin>>a[n].L>>a[n].R, a[n].L||a[n].R)
            ++n;
        sort(a, a + n);
        int ans = 1, R = a[0].R;
        for (int i = 1; i < n; i++)
        {
            if (a[i].L >= R)
            {
                ++ans;
                R = a[i].R;
            }
        }
        cout << ans << '\n';
    }
}


區間選點問題
//problem
給你 n 條線段區間為 [Li,Ri]，
請問至少要取幾個點才能讓每個區間至少包含一個點?

//solution
將區間依照右界由小到大排序，R=第一個區間的右界，
遍歷所有區段，如果當前區間左界>R ，
代表必須多選一個點 (ans+=1)，並將 R=當前區間右界。

//problem
給定 N 個座標，要在 x 軸找到最小的點，
讓每個座標至少和一個點距離 ≤ D。

//solution
以每個點 (xi,yi) 為圓心半徑為 D 的圓 C，
求出 C 和 x 軸的交點 Li,Ri，題目轉變成區間選點問題。

//code
struct Line
{
    int L, R;
    bool operator<(const Line &rhs) const { 
        return R < rhs.R;
        }
};

int main()
{
    int t;
    cin >> t;
    Line a[30];
    while (t--)
    {
        int n = 0;
        while (cin>>a[n].L>>a[n].R, a[n].L||a[n].R)
            ++n;
        sort(a, a + n);
        int ans = 1, R = a[0].R;
        for (int i = 1; i < n; i++)
        {
            if (a[i].L >= R)
            {
                ++ans;
                R = a[i].R;
            }
        }
        cout << ans << '\n';
    }
}


最小化最大延遲問題
//problem
給定 N 項工作，每項工作的需要處理時長為 Ti，
期限是 Di，第 i 項工作延遲的時間為 Li=max(0,Fi−Di)，
原本Fi 為第 i 項工作的完成時間，
求一種工作排序使 maxLi 最小。

//solution
按照到期時間從早到晚處理。

//code
struct Work
{
    int t, d;
    bool operator<(const Work &rhs) const {
        return d < rhs.d;
        }
};

int main()
{
    int n;
    Work a[10000];
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].t >> a[i].d;
    sort(a, a + n);
    int maxL = 0, sumT = 0;
    for (int i = 0; i < n; ++i)
    {
        sumT += a[i].t;
        maxL = max(maxL, sumT - a[i].d);
    }
    cout << maxL << '\n';
}


最少延遲數量問題
//problem
給定 N 個工作，每個工作的需要處理時長為 Ti，
期限是 Di，求一種工作排序使得逾期工作數量最小。

//solution
期限越早到期的工作越先做。將工作依照到期時間從早到晚排序，
依序放入工作列表中，如果發現有工作預期，
就從目前選擇的工作中，移除耗時最長的工作。

上述方法為 Moore-Hodgson s Algorithm。

//problem
給定烏龜的重量和可承受重量，問最多可以疊幾隻烏龜?

和最少延遲數量問題是相同的問題，只要將題敘做轉換。

工作處裡時長 → 烏龜重量
工作期限 → 烏龜可承受重量
多少工作不延期 → 可以疊幾隻烏龜

//code
struct Work{
    int t, d;
    bool operator<(const Work &rhs) const { 
        return d < rhs.d; 
        }
};

int main()
{
    int n = 0;
    Work a[10000];
    priority_queue<int> pq;
    while(cin >> a[n].t >> a[n].d)
        ++n;
    sort(a, a + n);
    int sumT = 0, ans = n;
    for (int i = 0; i < n; ++i)
    {
        pq.push(a[i].t);
        sumT += a[i].t;
        if(a[i].d<sumT)
        {
            int x = pq.top();
            pq.pop();
            sumT -= x;
            --ans;
        }   
    }
    cout << ans << '\n';
}

任務調度問題
//problem
給定 N 項工作，每項工作的需要處理時長為 Ti，
期限是 Di，如果第 i 項工作延遲需要受到 pi 單位懲罰，
請問最少會受到多少單位懲罰。

//solution
依照懲罰由大到小排序，
每項工作依序嘗試可不可以放在 Di−Ti+1,Di−Ti,...,1,0，
如果有空閒就放進去，否則延後執行。

//problem
給定 N 項工作，每項工作的需要處理時長為 Ti，
期限是 Di，如果第 i 項工作在期限內完成會獲得 ai 單位獎勵，
請問最多會獲得多少單位獎勵。

//solution
和上題相似，這題變成依照獎勵由大到小排序。

//code
struct Work
{
    int d, p;
    bool operator<(const Work &rhs) const { 
        return p > rhs.p; 
        }
};

int main()
{
    int n;
    Work a[100005];
    bitset<100005> ok;
    while (cin >> n)
    {
        ok.reset();
        for (int i = 0; i < n; ++i)
            cin >> a[i].d >> a[i].p;
        sort(a, a + n);
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int j = a[i].d;
            while (j--)
                if (!ok[j])
                {
                    ans += a[i].p;
                    ok[j] = true;
                    break;
                }
        }
        cout << ans << '\n';
    }
}

多機調度問題
//problem
給定 N 項工作，每項工作的需要處理時長為 Ti，
有 M 台機器可執行多項工作，但不能將工作拆分，
最快可以在什麼時候完成所有工作?

//solution
將工作由大到小排序，每項工作交給最快空閒的機器。

//code
int main()
{
    int n, m;
    int a[10000];
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n,greater<int>());
    int ans = 0;
    priority_queue<int,vector<int>,greater<int>>pq;
    for (int i = 0; i < m && i < n; ++i)
    {
        ans = max(ans, a[i]);
        pq.push(a[i]);
    }
    for (int i = m; i < n; ++i)
    {
        int x = pq.top();
        pq.pop();
        x += a[i];
        ans = max(ans, x);
        pq.push(x);
    }
    cout << ans << '\n';
}




