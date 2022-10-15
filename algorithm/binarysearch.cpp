#include <bits/stdc++.h>
using namespace std;

int binary_search(vector<int> &nums, int target) {
    int left=0, right=nums.size()-1;
    while(left<=right){
        int mid=(left+right)/2; 
        if (nums[mid]>target) right=mid-1;
        else if(nums[mid]<target) left=mid+1;
        else return mid+1;
    }
    return 0;
}
	
int main() {
	int n, k, x;
	cin >> n >> k;
	int a[n];
	vector<int> v;
	for(int i=0 ; i<n ; i++){
		cin >> x;
		v.push_back(x);
	}
	for(int i=0 ; i<k ; i++) cin >> a[i];
	for(int i=0 ; i<k ; i++){
		cout << binary_search(v, a[i]) << endl;
	}
}

lower_bound(a, a + n, k);     //最左邊 ≥ k 的位置
upper_bound(a, a + n, k);     //最左邊 > k 的位置
upper_bound(a, a + n, k) - 1; //最右邊 ≤ k 的位置
lower_bound(a, a + n, k) - 1; //最右邊 < k 的位置
(lower_bound, upper_bound)    //等於 k 的範圍
equal_range(a, a+n, k);

/*
input
5 5
1 3 4 7 9
3 1 9 7 -2
*/

/*
output
2
1
5
4
0
*/