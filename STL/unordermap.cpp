map：存放 key-value pairs 的映射資料結構，會按 key 由小到大排序。
宣告：
map <int, int> mp; // key和value都是整數
加入新的key-value pair：
mp[key] = value;
檢查 key 是否存在 map 中：
mp.count(key);
刪除 key：
mp.erase(key);
清空 map 中的所有元素：
mp.clear();
利用 key 取值：
value = mp[key];
判斷是否為空的map：
mp.empty() 回傳true
mp.size() 回傳零
【範例】ZeroJudge a135: 12250 – Language Detection 【題解】
遍歷整個map時，利用iterator操作：
取key：it->first 或 (*it).first
取value：it->second 或 (*it).second