int binary_search(int target) {
// For range [ok, ng) or (ng, ok], "ok" is for the
// index that target value exists, with "ng" doesn't.
    int ok = maxn, ng = -1;
// For first lower_bound, ok=maxn and ng=-1,
// for last lower_bound, ok = -1 and ng = maxn
// (the "check" funtion
// should be changed depending on it.)
    while(abs(ok - ng) > 1) {
        int mid = (ok + ng) >> 1;
        if(check(mid)) ok = mid;    
        else ng = mid;
// Be careful, "arr[mid]>=target" for first
// lower_bound and "arr[mid]<=target" for
// last lower_bound. For range (ng, ok],
// convert it into (ng, mid] and (mid, ok] than
// choose the first one, or convert [ok, ng) into
// [ok, mid) and [mid, ng) and than choose
// the second one.
    }
    return ok;
}

lower_bound(arr, arr + n, k);    //最左邊 ≥ k 的位置
upper_bound(arr, arr + n, k);    //最左邊 > k 的位置
upper_bound(arr, arr + n, k) - 1;//最右邊 ≤ k 的位置
lower_bound(arr, arr + n, k) - 1;//最右邊 < k 的位置
(lower_bound, upper_bound)       //等於 k 的範圍
equal_range(arr, arr+n, k);