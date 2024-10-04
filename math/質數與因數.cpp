歐拉篩O(n)
#define MAXN 47000 //sqrt(2^31)=46,340...
bool isPrime[MAXN];
int p[MAXN];
int pSize=0;
void getPrimes(){
  memset(isPrime,true,sizeof(isPrime));
  isPrime[0]=isPrime[1]=false;
  for(int i=2;i<MAXN;i++){
    if(isPrime[i]) p[pSize++]=i;
    for(int j=0;j<pSize&&i*p[j]<=MAXN;++j){
      isPrime[i*p[j]]=false;
      if(i%p[j]==0) break;
    }
  }
}

最大公因數 O(log(min(a,b))) 
int GCD(int a, int b){
  if(b == 0) return a;
  return GCD(b, a%b);
}

質因數分解
void primeFactorization(int n){
  for(int i=0; i<p.size(); ++i) {
    if(p[i]*p[i] > n) break;
    if(n % p[i]) continue;
    cout << p[i] << ' ';
    while(n%p[i] == 0) n /= p[i]; 
  }
  if(n != 1) cout << n << ' ';
  cout << '\n';
}

擴展歐幾里得算法 ax + by = GCD(a, b)
int ext_euc(int a, int b, int &x, int &y) {
  if(b == 0){
    x = 1, y = 0;
    return a;
  }
  int d = ext_euc(b, a%b, y, x);
  y -= a/b*x;
  return d;
}
int main(){
  int a, b, x, y;
  cin >> a >> b;
  ext_euc(a, b, x, y);
  cout << x << ' ' << y << endl;
  return 0;
}

歌德巴赫猜想
解: 把偶數 N (6≤N≤10^6) 寫成兩個質數的和。
#define N 20000000
int ox[N], p[N], pr;
void PrimeTable(){
  ox[0] = ox[1] = 1;
  pr = 0;
  for(int i=2;i<N;i++){
    if(!ox[i]) p[pr++] = i;
    for(int j=0; i*p[j]<N&&j<pr; j++)
      ox[i*p[j]] = 1;
  }
}
int main(){
  PrimeTable();
  int n; 
  while(cin>>n, n){
    int x;
    for(x=1;; x+=2)
      if(!ox[x] && !ox[n-x]) break;
    printf("%d = %d + %d\n", n, x, n-x);
  }
}

problem : 
給定整數 N，求N最少可以拆成多少個質數的和。
如果N是質數，則答案為 1。
如果N是偶數(N!=2)，則答案為2(強歌德巴赫猜想)。
如果N是奇數且N−2是質數，則答案為2(2+質數)。
其他狀況答案為 3 (弱歌德巴赫猜想)。

bool isPrime(int n){
  for(int i=2;i<n;++i){
    if(i*i>n) return true;
    if(n%i==0) return false;
  }
  return true;
}
int main(){
  int n;
  cin>>n;
  if(isPrime(n)) cout<<"1\n";
  else if(n%2==0||isPrime(n-2)) cout<<"2\n";
  else cout<<"3\n";
}