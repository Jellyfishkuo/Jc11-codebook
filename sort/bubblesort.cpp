#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	int a[n], tmp;
	for(int i=0; i<n; i++) cin>>a[i];
	for(int i=n-1; i>0; i--) {
		for(int j=0; j<=i-1; j++) {
			if( a[j]>a[j+1]) {
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}
		}
	}
	for(int i=0; i<n; i++) cout<<a[i]<<" ";
}