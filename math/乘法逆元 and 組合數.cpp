using ll = long long;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;

int fact[maxn] = {1, 1};    // x! % mod
int inv[maxn] = {1, 1};     // x^(-1) % mod
int invFact[maxn] = {1, 1}; // (x!)^(-1) % mod

void build() {
  for(int x=2; x<maxn; x++) {
    fact[x] = (ll)x * fact[x-1] % mod;
    inv[x] = (ll)(mod-mod/x)*inv[mod%x]%mod;
    invFact[x] = (ll)invFact[x-1]*inv[x]%mod;
  }
}

// 前提：mod 為質數
void build() {
  auto qpow = [&](ll a, int b) {
    ll res = 1;
    for(; b; b>>=1) {
      if(b & 1) res = res * a % mod;
      a = a * a % mod;
    }
    return res;
  };
  
  for(int x=2; x<maxn; x++) {
    fact[x] = (ll)x * fact[x-1] % mod;
    invFact[x] = qpow(fact[x], mod-2);
  }
}

// C(a, b) % mod
int comb(int a, int b) {
  if(a < b) return 0;
  ll x = fact[a];
  ll y = (ll)invFact[b] * invFact[a-b] % mod;
  return x * y % mod;
}