#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
//權值線段樹 + 離散化 解決區間第k小問題
//其他網路上的解法: 2個heap，Treap，AVL tree
#define maxn 30005
int nums[maxn];
int getArr[maxn];
int id[maxn];
int st[maxn << 2];
void update(int index, int l, int r, int qx)
{
    if (l == r)
    {
        ++st[index];
        return;
    }

    int mid = (l + r) / 2;
    if (qx <= mid)
        update(index * 2, l, mid, qx);
    else
        update(index * 2 + 1, mid + 1, r, qx);
    st[index] = st[index * 2] + st[index * 2 + 1];
}
//找區間第k個小的
int query(int index, int l, int r, int k)
{
    if (l == r)
        return id[l];
    int mid = (l + r) / 2;
    //k比左子樹小
    if (k <= st[index * 2])
        return query(index * 2, l, mid, k);
    else
        return query(index * 2 + 1, mid + 1, r, k - st[index * 2]);
}
int main()
{
    int t;
    cin >> t;
    bool first = true;
    while (t--)
    {
        if (first)
            first = false;
        else
            puts("");
        memset(st, 0, sizeof(st));
        int m, n;
        cin >> m >> n;
        for (int i = 1; i <= m; ++i)
        {
            cin >> nums[i];
            id[i] = nums[i];
        }
        for (int i = 0; i < n; ++i)
            cin >> getArr[i];
        //離散化
        //防止m == 0
        if (m)
            sort(id + 1, id + m + 1);
        int stSize = unique(id + 1, id + m + 1) - (id + 1);
        for (int i = 1; i <= m; ++i)
        {
            nums[i] = lower_bound(id + 1, id + stSize + 1, nums[i]) - id;
        }
        int addCount = 0;
        int getCount = 0;
        int k = 1;
        while (getCount < n)
        {
            if (getArr[getCount] == addCount)
            {
                printf("%d\n", query(1, 1, stSize, k));
                ++k;
                ++getCount;
            }
            else
            {
                update(1, 1, stSize, nums[addCount + 1]);
                ++addCount;
            }
        }
    }
    return 0;
}