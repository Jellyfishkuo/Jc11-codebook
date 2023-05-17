#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <cassert>
#include <chrono>
#include <algorithm>
using namespace std;

template <typename T = int>
vector<T> randomvec(int n){
    vector<T> vec(n);
    unsigned seed=chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0,200.0);
    for(T &num:vec) num=distribution(generator);
    return vec;
}

template <typename T>
bool AssertVectorIsSorted(vector<T>& vec){
    for(int i=0;i<(int)vec.size()-1;++i)
        if(vec[i]>vec[i+1]) return false;
    return true;
}

template <typename T>
void printvector(vector<T>& vec){
    for(T &x:vec) cout<<x<<" ";
    cout<<"\n";
    return;
}

int main(){
    int n;
    string s;
    while(cin>>n>>s){
        if(s=="int"){
            vector<int> vec=randomvec<int>(n);
            printvector(vec);
            sort(vec.begin(), vec.end());
            printvector(vec);
            assert(AssertVectorIsSorted(vec));
        }
        else{
            vector<double> vec=randomvec<double>(n);
            printvector(vec);
            sort(vec.begin(), vec.end());
            printvector(vec);
            assert(AssertVectorIsSorted(vec));
        }
        cout<<"True\n";
    }
    return 0;
}
