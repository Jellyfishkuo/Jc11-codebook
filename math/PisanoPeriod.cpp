/*Pisano Period: 
  費氏數列在mod n的情況下會有循環週期，
  且週期的結束判斷會在
  fib[i - 1] == 0 && fib[i] == 1時，
  此時循環週期長度是i - 1
  Pisano period可證一個週期的長度會在[n, n ^ n]之間
  mod 1都等於0，沒有週期*/