while True:
  try:
    n = int(input())           # 有幾筆數字需要排序
    arr = []                   # 建立空串列
    for i in range(n):
      arr.append(int(input())) # 依序將數字存入串列
    arr.sort()                 # 串列排序
    for i in arr:
      print(i)                 # 依序印出串列中每個項目
  except:
    break