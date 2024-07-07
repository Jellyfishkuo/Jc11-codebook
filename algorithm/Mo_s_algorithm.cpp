/*利用prefix前綴XOR和
  如果要求[x, y]的XOR和只要回答prefix[y] ^ prefix[x - 1]即可在O(1)回答
  同時維護cnt[i]代表[x, y]XOR和 == i的個數
  如此我們知道[l, r]可以快速知道[l - 1, r], [l + 1, r], [l, r - 1], [l, r + 1]的答案
  就符合Mo's algorithm的思維O(N * sqrt(n))
  每次轉移為O(1)，具體轉移方法在下面*/
#define maxn 100005
//在此prefix[i]是[1, i]的XOR和
int prefix[maxn];
//log_2(1000000) = 19.931568569324174087221916576937...
//所以開到1 << 20
//cnt[i]代表的是有符合nums[x, y] such that nums[x] ^ nums[x + 1] ^ .. ^ nums[y] == i
//的個數
long long cnt[1 << 20];
//塊大小 -> sqrt(n)
int sqrtQ;
struct Query {
    int l, r, id;
    bool operator < (const Query& other) const {
        if (this->l / sqrtQ != other.l / sqrtQ)
            return this->l < other.l;
        //奇偶排序(優化)
        if (this->l / sqrtQ & 1)
            return this->r < other.r;
        return this->r > other.r;
    }
};
Query querys[maxn];
long long ans[maxn];
long long res = 0;
int k;
void add(int x) {
    res += cnt[k ^ prefix[x]];
    ++cnt[prefix[x]];
}
void sub(int x) {
    --cnt[prefix[x]];
    res -= cnt[k ^ prefix[x]];
}
int main() {
    int n, m;
    scanf("%d %d %d", &n, &m, &k);
    sqrtQ = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &prefix[i]);
        prefix[i] ^= prefix[i - 1];
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &querys[i].l, &querys[i].r);
        //減1是因為prefix[i]是[1, i]的前綴XOR和，所以題目問[l, r]我們要回答[l - 1, r]的答案
        --querys[i].l;
        querys[i].id = i;
    }
    sort(querys + 1, querys + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (l < querys[i].l) {
            sub(l);
            ++l;
        }
        while (l > querys[i].l) {
            --l;
            add(l);
        }
        while (r < querys[i].r) {
            ++r;
            add(r);
        }
        while (r > querys[i].r) {
            sub(r);
            --r;
        }
        ans[querys[i].id] = res;
    }
    for (int i = 1; i <= m; ++i){
        printf("%lld\n", ans[i]);
    }
    return 0;
}