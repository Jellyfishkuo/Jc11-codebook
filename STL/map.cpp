#include <bits/stdc++.h>
using namespace std;

元素存取
operator[]：存取指定的[i]元素的資料
迭代器
begin()：回傳指向map頭部元素的迭代器
end()：回傳指向map末尾的迭代器
rbegin()：回傳一個指向map尾部的反向迭代器
rend()：回傳一個指向map頭部的反向迭代器
容量
empty()：檢查容器是否為空，空則回傳true
size()：回傳元素數量
max\_size()：回傳可以容納的最大元素個數
修改器
clear()：刪除所有元素
insert()：插入元素
erase()：刪除一個元素
swap()：交換兩個map
查找
count()：回傳指定元素出現的次數
find()：查找一個元素

int main(){

    //declaration container and iterator
    map<string, string> mp;
    map<string, string>::iterator iter;
    map<string, string>::reverse_iterator iter_r;

    //insert element
    mp.insert(pair<string, string>("r000", "student_zero"));

    mp["r123"] = "student_first";
    mp["r456"] = "student_second";

    //traversal
    for(iter = mp.begin(); iter != mp.end(); iter++)
        cout<<iter->first<<" "<<iter->second<<endl;
    for(iter_r = mp.rbegin(); iter_r != mp.rend(); iter_r++)
        cout<<iter_r->first<<" "<<iter_r->second<<endl;

    //find and erase the element
    iter = mp.find("r123");
    mp.erase(iter);

    iter = mp.find("r123");

    if(iter != mp.end())
       cout<<"Find, the value is "<<iter->second<<endl;
    else
       cout<<"Do not Find"<<endl;

    return 0;
}