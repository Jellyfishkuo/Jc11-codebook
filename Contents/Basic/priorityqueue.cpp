priority_queue <int> pq;

pq.push(x);

x = pq.top();
pq.pop(); // delete after read

pq.empty() //return true
pq.size() //return 0

priority_queue<T> pq; //from big to small 
priority_queue<T, vector<T>, greater<T> > pq; 
                         //from small to big
priority_queue<T, vector<T>, cmp> pq; //cmp