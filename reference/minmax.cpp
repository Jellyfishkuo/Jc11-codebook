#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> num 
        = {4, 2, 8, 5, 1, 9, 6, 3, 7};
    sort(num.begin(), num.end());
    int target = 5;
    vector<int>::iterator it=
        lower_bound(num.begin(),num.end(),target);
    if (it!=num.end()&&*it==target) {
        int index=distance(num.begin(), it);
        cout<<target<<" 在 "<<index<<endl;
    } 
    else
        cout<<target<<" 未找到！"<<endl;    
    pair<vector<int>::iterator, vector<int>::iterator> 
        minmaxElement = minmax_element(num.begin(), num.end());
    cout<<"最小元素："<<*(minmaxElement.first)<<endl;
    cout<<"最大元素："<<*(minmaxElement.second)<<endl;
    return 0;
}
