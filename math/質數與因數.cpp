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