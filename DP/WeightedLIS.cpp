/*概念基本上與LIS相同，但不能用greedy的LIS，所以只能用dp版LIS
  但有個問題是dp版要O(n^2)
  n最大200000一定超時，所以這題要改一下dp的LIS
  在DP版中有一層迴圈是要往前搜height[j] < height[i](j in 1 ~ i - 1)的然後挑B[j]最大的
  這for loop造成O(n ^ 2)
  注意到子問題是在1 ~ i - 1中挑出B[j]最大的
  這一步可以用線段樹優化
  所以最後可以在O(nlogn)完成*/
#define maxn 200005
long long dp[maxn];
long long height[maxn];
long long B[maxn];
long long st[maxn << 2];
void update(int p, int index, int l, int r, long long v) {
    if (l == r) {
        st[index] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        update(p, (index << 1), l, mid, v);
    else
        update(p, (index << 1) + 1, mid + 1, r, v);
    st[index] = max(st[index << 1], st[(index << 1) + 1]);
}
long long query(int index, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return st[index];
    int mid = (l + r) >> 1;
    long long res = -1;
    if (ql <= mid)
        res = max(res, query(index << 1, l, mid, ql, qr));
    if (mid < qr)
        res = max(res, query((index << 1) + 1, mid + 1, r, ql, qr));
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &height[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &B[i]);
    long long res = B[1];
    update(height[1], 1, 1, n, B[1]);
    for (int i = 2; i <= n; ++i) {
        long long temp;
        if (height[i] - 1 >= 1)
            temp = B[i] + query(1, 1, n, 1, height[i] - 1);
        else
            temp = B[i];
        update(height[i], 1, 1, n, temp);
        res = max(res, temp);
    }
    printf("%lld\n", res);
    return 0;
}