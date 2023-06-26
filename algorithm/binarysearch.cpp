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

lower_bound(a, a + n, k);     //最左邊 ≥ k 的位置
upper_bound(a, a + n, k);     //最左邊 > k 的位置
upper_bound(a, a + n, k) - 1; //最右邊 ≤ k 的位置
lower_bound(a, a + n, k) - 1; //最右邊 < k 的位置
(lower_bound, upper_bound)    //等於 k 的範圍
equal_range(a, a+n, k);