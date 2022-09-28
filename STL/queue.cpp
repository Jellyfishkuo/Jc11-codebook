queue：佇列，資料有「先進先出」 (first in first out, FIFO)的特性。
就像排隊買票一樣，先排隊的客戶被服務。
宣告：
    queue <int> q;  
把元素 x 加進 queue：
    q.push(x);
取值：
    x = q.front();
移除已經讀取的值：
    q.pop();
判斷是否為空的queue：
    q.empty() 回傳true
    q.size() 回傳零

#include <iostream>
#include <queue>
using namespace std;
  
int main() {
    int n;
    while (cin >> n){
        if (n == 0) break;
        queue <int> q;
        for (int i = 0; i < n; i++){
            q.push(i+1);
        }
        cout << "Discarded cards:";
        for (int i = 0; i < n-1; i++){
            if (i != 0) cout << ',';
            cout << ' ' << q.front();
            q.pop();
            q.push(q.front());
            q.pop();
        }
        cout << endl << "Remaining card: " << q.front() << endl;
    }
}