// 以下經過check()後 . 為false，o 為true
//皆為[l, r]區間
//.....voooooo 即答案左邊界，符合條件最小的
int bsearch(int l, int r)
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

//ooooov..... 即答案右邊界，符合條件最大的
int bsearch(int l, int r)
{
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}