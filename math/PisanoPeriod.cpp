#include <cstdio>
#include <vector>
using namespace std;

/*
Pisano Period + 快速冪 + mod
Pisano Period: 
    費氏數列在mod n的情況下會有循環週期，
    且週期的結束判斷會在fib[i - 1] == 0 && fib[i] == 1時，
    此時循環週期長度是i - 1

所以這題是在找出循環週期後，
用快速冪並mod(循環週期長度)即可AC(快速冪記得mod)，
此外fib要mod n，也要找週期，所以用預處理的方式列表
*/

#define maxn 1005

/*
Pisano period可證一個週期的長度會在[n, n ^ n]之間
*/
//很可惜，會爆
// int fib[maxn][maxn * maxn];
//改用vector
vector<int> fib[maxn];
int period[maxn];

int qpow(int a, unsigned long long b, int mod)
{
  if (b == 0)
    return a;
  long long res = 1;
  while (b)
  {
    if (b & 1)
      res = ((a % mod) * (res % mod)) % mod;
    a = ((a % mod) * (a % mod)) % mod;
    b >>= 1;
  }
  return res;
}

int main()
{
  int t;
  unsigned long long a, b;
  int n;

  //注意: 這裡沒算mod 1的循環長度，
  //因為mod 1都等於0，沒有週期
  for (int i = 2; i < maxn; ++i)
  {
    fib[i].emplace_back(0);
    fib[i].emplace_back(1);
    for (int j = 2; j < maxn * maxn; ++j)
    {
      fib[i].emplace_back(
        (fib[i][j-1]%i+fib[i][j-2]%i)%i
      );
      if (fib[i][j-1]==0&&fib[i][j]==1)
      {
        period[i] = j - 1;
        break;
      }
    }
  }

  scanf("%d", &t);

  while (t--)
  {
    scanf("%llu %llu %d", &a, &b, &n);
    if (a == 0)
      puts("0");
    else if (n == 1)  //當mod 1時任何數都是0，
      puts("0");      //所以直接輸出0，避免我們沒算
    else              //fib[1][i]的問題(Runtime error)
      printf("%d\n",
        fib[n][qpow(a % period[n], b, period[n])]);
  }
  return 0;
}