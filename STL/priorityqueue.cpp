priority_queue <int> pq;  //宣告

pq.push(x);

x = pq.top();
pq.pop();                 //讀取後刪除

pq.empty()                //回傳true
pq.size()                 //回傳0

priority_queue<T> pq;     //預設由大到小 
priority_queue<T, vector<T>, greater<T> > pq; 
                          //改成由小到大
priority_queue<T, vector<T>, cmp> pq;   //cmp