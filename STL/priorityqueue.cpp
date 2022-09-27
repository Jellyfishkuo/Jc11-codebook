priority_queue： 優先隊列，資料預設由大到小排序，即優先權高的資料會先被取出。
宣告：
    priority_queue <int> pq;
把元素 x 加進 priority_queue：
    pq.push(x);
讀取優先權最高的值：
    x = pq.top();
    pq.pop();                 //讀取後刪除
判斷是否為空的priority_queue：
    pq.empty()                //回傳true
    pq.size()                 //回傳0
如需改變priority_queue的優先權定義：
    priority_queue<T> pq;     //預設由大到小 
    priority_queue<T, vector<T>, greater<T> > pq; 
                            //改成由小到大
    priority_queue<T, vector<T>, cmp> pq;   //cmp