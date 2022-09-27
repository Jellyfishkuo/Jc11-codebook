min： 取最小值。
min(a, b)
min(list)
max： 取最大值。
max(a, b)
max(list)
min_element： 找尋最小元素
min_element(first, last)
max_element： 找尋最大元素
max_element(first, last)
sort： 排序，預設由小排到大。
sort(first, last)
sort(first, last, comp)： 可自行定義比較運算子 Comp 。
find： 尋找元素。
find(first, last, val)
lower_bound： 尋找第一個小於 x 的元素位置，如果不存在，則回傳 last 。
lower_bound(first, last, val)
upper_bound： 尋找第一個大於 x 的元素位置，如果不存在，則回傳 last 。
upper_bound(first, last, val)
next_permutation： 將序列順序轉換成下一個字典序，如果存在回傳 true ，反之回傳 false 。
next_permutation(first, last)
prev_permutation： 將序列順序轉換成上一個字典序，如果存在回傳 true ，反之回傳 false 。
prev_permutation(first, last)