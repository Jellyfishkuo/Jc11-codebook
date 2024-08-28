const int maxn = 1e6 + 10;

int n, m;               // len(a), len(b)
int f[maxn];            // failure function
char a[maxn], b[maxn];

void failureFuntion() { // f[0] = 0
    for(int i=1, j=0; i<m; ) {
        if(b[i] == b[j]) f[i++] = ++j;
        else if(j) j = f[j-1];
        else f[i++] = 0;
    }
}

int kmp() {
    int i = 0, j = 0, res = 0;
    while(i < n) {
        if(a[i] == b[j]) i++, j++;
        else if(j) j = f[j-1];
        else i++;
        if(j == m) {
            res++;  // 找到答案
            j = 0;  // non-overlapping
        }
    }
    return res;
}

// Problem: 所有在b裡，前後綴相同的長度
// b = ababcababababcabab
// f = 001201234123456789
// 前9 = 後9
// 前4 = 前9的後4 = 後4
// 前2 = 前4的後2 = 前9的後2 = 後2
for(int j=m; j; j=f[j-1]) {
    // j 是答案
}