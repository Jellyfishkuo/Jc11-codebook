unordered_set 的實作方式通常是用雜湊表(hash table)，
資料插入和查詢的時間複雜度很低，為常數級別O(1)，
相對的代價是消耗較多的記憶體，空間複雜度較高，
無自動排序功能。

初始化
unordered_set<int> myunordered_set{1, 2, 3, 4, 5}; 

陣列初始化
int arr[] = {1, 2, 3, 4, 5};
unordered_set<int> myunordered_set(arr, arr+5);

插入元素
unordered_set<int> myunordered_set;
myunordered_set.insert(1);

迴圈遍歷 unordered_set 容器
#include <iostream>
#include <unordered_set>
using namespace std;
int main() {
    unordered_set<int> myunordered_set = {3, 1};
    myunordered_set.insert(2);
    myunordered_set.insert(5);
    myunordered_set.insert(4);
    myunordered_set.insert(5);
    myunordered_set.insert(4);
    for (const auto &s : myunordered_set)
        cout << s << " ";
    cout << "\n";
    return 0;
}

/*
output
4 5 2 1 3
*/

unordered_set 刪除指定元素
#include <iostream>
#include <unordered_set>
int main() {
    unordered_set<int> myunordered_set{2, 4, 6, 8};
    myunordered_set.erase(2);
    for (const auto &s : myunordered_set)
        cout << s << " ";
    cout << "\n";
    return 0;
}
/*
output
8 6 4
*/

清空 unordered_set 元素
unordered_set<int> myunordered_set;
myunordered_set.insert(1);
myunordered_set.clear();

unordered_set 判斷元素是否存在
unordered_set<int> myunordered_set;
myunordered_set.insert(2);
myunordered_set.insert(4);
myunordered_set.insert(6);
cout << myunordered_set.count(4) << "\n"; // 1
cout << myunordered_set.count(8) << "\n"; // 0

判斷 unordered_set 容器是否為空
#include <iostream>
#include <unordered_set>

int main() {
    unordered_set<int> myunordered_set;
    myunordered_set.clear();
    if(myunordered_set.empty())
        cout<<"empty\n";
    else 
        cout<<"not empty, size is "<<myunordered_set.size()<<"\n";
    return 0;
}
