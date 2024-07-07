#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
/*題意: 給定一個W矩陣，現在分成row、column兩個1維陣列
    W[i][j]=k即代表column[i] + row[j]要>=k
    求row[] 與 column[]的所有值在滿足矩陣W的要求之下
    row[] + column[]所有元素相加起來要最小
    利用KM求二分圖最大權匹配
    Lx -> vertex labeling of X
    Ly -> vertex labeling of y
    一開始Lx[i] = max(W[i][j]), Ly = 0
    Lx[i] + Ly[j] >= W[i][j]
    要最小化全部的(Lx[i] + Ly[j])加總
    不斷的調整vertex labeling去找到一條交錯邊皆滿足Lx[i] + Ly[j] == W[i][j]的增廣路
    最後會得到正確的二分圖完美匹配中的最大權分配(先滿足最多匹配，再滿足最大權)
    意義是將最大化所有匹配邊權重和的問題改成最小化所有點的權重和*/
#define maxn 505
int W[maxn][maxn];
int Lx[maxn], Ly[maxn];
bool S[maxn], T[maxn];
//L[i] = j -> S_i配給T_j, -1 for 還沒匹配
int L[maxn];
int n;
bool match(int i) {
    S[i] = true;
    for (int j = 0; j < n; ++j) {
        // KM重點
        // Lx + Ly >= selected_edge(x, y)
        // 要想辦法降低Lx + Ly
        // 所以選Lx + Ly == selected_edge(x, y)
        if (Lx[i] + Ly[j] == W[i][j] && !T[j]) {
            T[j] = true;
            if ((L[j] == -1) || match(L[j])) {
                L[j] = i;
                return true;
            }
        }
    }
    return false;
}
// 修改二分圖上的交錯路徑上點的權重
// 此舉是在通過調整vertex labeling看看能不能產生出新的增廣路(KM的增廣路要求Lx[i] + Ly[j] == W[i][j])
// 在這裡優先從最小的diff調調看，才能保證最大權重匹配
void update()
{
    int diff = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) {
        if (S[i]) {
            for (int j = 0; j < n; ++j) {
                if (!T[j])
                    diff = min(diff, Lx[i] + Ly[j] - W[i][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (S[i]) Lx[i] -= diff;
        if (T[i]) Ly[i] += diff;
    }
}
void KM()
{
    for (int i = 0; i < n; ++i) {
        L[i] = -1;
        Lx[i] = Ly[i] = 0;
        for (int j = 0; j < n; ++j)
            Lx[i] = max(Lx[i], W[i][j]);
    }
    for (int i = 0; i < n; ++i) {
        while(1) {
            memset(S, false, sizeof(S));
            memset(T, false, sizeof(T));
            if (match(i))
                break;
            else
                update(); //去調整vertex labeling以增加增廣路徑
        }
    }
}
int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &W[i][j]);
        KM();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (i != 0)
                printf(" %d", Lx[i]);
            else
                printf("%d", Lx[i]);
            res += Lx[i];
        }
        puts("");
        for (int i = 0; i < n; ++i) {
            if (i != 0)
                printf(" %d", Ly[i]);
            else
                printf("%d", Ly[i]);
            res += Ly[i];
        }
        puts("");
        printf("%d\n", res);
    }
    return 0;
}