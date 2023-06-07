#include<iostream>
#include<vector>
using namespace std;
template<typename T>
int p(vector<T>& arr,int low,int high){
    T pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++)
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    swap(arr[i+1],arr[high]);
    return 1+i;
}
template<typename T>
void qsort(vector<T>& arr, int low,int high){
    if(low<high){
        int pindex=p(arr,low,high);
        qsort(arr,low,pindex-1);
        qsort(arr,pindex+1,high);
    }
}
template<typename T>
void mysort(vector<T>& arr){
    int n=arr.size();
    qsort(arr,0,n-1);
}
template<typename T>
void solve(vector<T>& arr){
    mysort(arr);
    int cnt=0;
    for(auto a:arr){
        if(cnt++) cout<<" ";
        cout<<a;
    }
    cout<<endl;
    arr.clear();
}
int main(){
    int n,x;
    double d;
    char c;
    string s;
    while(cin>>n){
        vector<int> v;
        for(int i=0;i<n;i++){
            cin>>x;
            v.push_back(x);
        }
        solve(v);
        cin>>n;
        vector<double> vd;
        for(int i=0;i<n;i++){
            cin>>d;
            vd.push_back(d);
        }
        solve(vd);
        cin>>n;
        vector<char> vc;
        for(int i=0;i<n;i++){
            cin>>c,vc.push_back(c);
        }
        solve(vc);
        cin>>n>>ws;
        vector<string> vs;
        for(int i=0;i<n;i++)
            getline(cin,s),vs.push_back(s);
        mysort(vs);
        for(auto a:vs) cout<<a<<endl;
        vs.clear();
    }
    return 0;
}