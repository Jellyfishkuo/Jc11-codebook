#include <cstdio>
//JosephusProblem，只是規定要先砍1號
//所以當作有n - 1個人，目標的13順移成12
//再者從0開始比較好算，所以目標12順移成11
int getWinner(int n, int k)
{
    int winner = 0;
    for (int i = 1; i <= n; ++i)
        winner = (winner + k) % i;
    return winner;
}
int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        --n;
        for (int k = 1; k <= n; ++k)
        {
            if (getWinner(n, k) == 11)
            {
                printf("%d\n", k);
                break;
            }
        }
    }
    return 0;
}