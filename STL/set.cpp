set： 集合，去除重複的元素，資料由小到大排序。
宣告：
    set <int> st;
把元素 x 加進 set：
    st.insert(x);
檢查元素 x 是否存在 set 中：
    st.count(x);
刪除元素 x：
    st.erase(x);      // 可傳入值或iterator
清空集合中的所有元素：
    st.clear();
取值： 使用iterator
    x = *st.begin();  // set中的第一個元素(最小的元素)。
    x = *st.rbegin(); // set中的最後一個元素(最大的元素)。
判斷是否為空的set：
st.empty() 回傳true
st.size() 回傳零
常用來搭配的member function：
st.count(x);
auto it = st.find(x); // binary search, O(log(N))
auto it = st.lower_bound(x); // binary search, O(log(N))
auto it = st.upper_bound(x); // binary search, O(log(N))
【multiset】
與 set 用法雷同，但會保留重複的元素，資料由小到大排序。
宣告：
multiset<int> st;
刪除資料：
st.erase(val); 會刪除所有值為 val 的元素。
st.erase(st.find(val)); 只刪除第一個值為 val 的元素。