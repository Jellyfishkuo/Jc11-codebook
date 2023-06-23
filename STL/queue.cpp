queue：佇列，資料有「先進先出」 (first in first out, FIFO)的特性。
就像排隊買票一樣，先排隊的客戶被服務。

取值：
    x = q.front(); //頭
    x = q.back();  //尾
移除已經讀取的值：
    q.pop();
判斷是否為空的queue：
    q.empty() 回傳true
    q.size() 回傳零