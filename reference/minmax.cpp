#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> num={5,3,3,3,6,6,74,3,-124,246,2456,-345};
    sort(num.begin(),num.end());
    pair<vector<int>::iterator,vector<int>::iterator> 
        minmaxElement=minmax_element(num.begin(),num.end());
    cout<<"sorted vector :\n";
    for(auto x:num) cout<<x<<" ";
    cout<<endl;
    cout<<*minmaxElement.first<<" "
        <<*minmaxElement.second<<endl;
}
