與 set 用法雷同，但會保留重複的元素。
資料由小到大排序。
宣告：
    multiset<int> st;
刪除資料：
    st.erase(val); 
    //會刪除所有值為 val 的元素。
    st.erase(st.find(val)); 
    //只刪除第一個值為 val 的元素。