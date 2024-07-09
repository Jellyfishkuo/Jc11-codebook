//區間dp
int dp[55][55]; 
// dp[i][j] -> [i,j]切割區間中最小的cost
int cuts[55];
int solve(int i, int j) {
    if (dp[i][j] != -1)
        return dp[i][j];
    //代表沒有其他切法，只能是cuts[j] - cuts[i]
    if (i == j - 1)
        return dp[i][j] = 0;
    int cost = 0x3f3f3f3f;
    for (int m = i + 1; m < j; ++m) {
        //枚舉區間中間切點
        cost = min(cost, solve(i, m) + 
          solve(m, j) + cuts[j] - cuts[i]);
    }
    return dp[i][j] = cost;
}
int main() {   
    int l,n;
    while (scanf("%d", &l) != EOF && l){
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &cuts[i]);
        cuts[0] = 0;
        cuts[n + 1] = l;
        memset(dp, -1, sizeof(dp));
        printf("ans = %d.\n", solve(0,n+1));
    }
    return 0;
}