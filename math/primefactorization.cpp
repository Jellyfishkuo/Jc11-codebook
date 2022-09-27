#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;    
	while(true) {
		cin>>n;
		for(int x=2; x<=n; x++) {
			while(n%x==0) {
				cout<<x<<"*";
				n/=x;
			}
		}
		cout<<"\b \n";
	}
	system("pause");
	return 0;
}