deque 是 C++ 標準模板函式庫（Standard Template Library, STL）
    中的雙向佇列容器（Double-ended Queue），跟 vector 相似，
    不過在 vector 中若是要添加新元素至開端，其時間複雜度為 O(N)，
    但在 deque 中則是 O(1)。同樣地，
    也能在我們需要儲存更多元素的時候自動擴展空間，
    讓我們不必煩惱佇列長度的問題。
dq.push_back()   //在 deque 的最尾端新增元素
dq.push_front()  //在 deque 的開頭新增元素
dq.pop_back()    //移除 deque 最尾端的元素
dq.pop_front()   //移除 deque 最開頭的元素
dq.back()        //取出 deque 最尾端的元素
dq.front()       //回傳 deque 最開頭的元素
dq.insert()
dq.insert(position, n, val)
    position: 插入元素的 index 值
    n: 元素插入次數
    val: 插入的元素值
dq.erase()       //刪除元素，需要使用迭代器指定刪除的元素或位置，同時也會返回指向刪除元素下一元素的迭代器。
dq.clear()       //清空整個 deque 佇列。
dq.size()        //檢查 deque 的尺寸
dq.empty()       //如果 deque 佇列為空返回 1； 若是存在任何元素，則返回 0
dq.begin()       //返回一個指向 deque 開頭的迭代器
dq.end()         //指向 deque 結尾，不是最後一個元素， 而是最後一個元素的下一個位置