#include<iostream>
#include<vector>
using namespace std;

template<typename T>
int partition(vector<T>& arr,int low,int high) {
    T pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++) {
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

template<typename T>
void quickSort(vector<T>& arr,int low,int high) {
    if(low<high){
        int pivotIndex=partition(arr,low,high);
        quickSort(arr,low,pivotIndex-1);
        quickSort(arr,pivotIndex+1,high);
    }
}

template<typename T>
void customSort(vector<T>& arr) {
    int n=arr.size();
    quickSort(arr,0,n-1);
}
int main(){
    vector<int> numbers={5, 2, 8, 1, 3};
    cout<<"Before sorting: ";
    for(const auto& num:numbers)
        cout<<num<<" ";
    customSort(numbers);
    cout<<"\nAfter sorting: ";
    for(const auto& num : numbers)
        cout<<num<<" ";
    return 0;
}