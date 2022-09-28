計算a^b
#include <iostream>
#define ll long long
using namespace std;

const ll MOD = 1000000007;
ll fp(ll a, ll b) {
	int ans = 1;
	while(b > 0) {
		if(b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ans;
}

int main() {
	int a, b;
	cin>>a>>b;
	cout<<fp(a,b);
}