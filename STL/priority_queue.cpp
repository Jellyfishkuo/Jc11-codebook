priority_queue：優先隊列，資料預設由大到小排序
宣告：
    priority_queue <int> pq;
把元素 x 加進 priority_queue：
    pq.push(x);
讀取優先權最高的值：
    x = pq.top();
    pq.pop(); // 讀取後刪除
判斷是否為空的priority_queue：
    pq.empty() //回傳true
    pq.size() //回傳零
如需改變priority_queue的優先權定義：
    priority_queue<T> pq; 預設由大排到小
    priority_queue<T, vector<T>, greater<T> > pq;  改成由小排到大
    priority_queue<T, vector<T>, cmp> pq; 自行定義 cmp 排序
自行定義 cmp，使用 struct：
    Overload operator()
    注意：因為優先判定為 !cmp，所以「由大排到小」需「反向」定義實現「最小值優先」。反之亦然。