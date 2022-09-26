[高維陣列先後順序]
int arr[10][10000]; 優於 int arr[10000][10];

[高度輸入輸出優化]
輸入整數
int read(){
    int res = 0 , f = 1; 
    char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-f; 
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        res=res*10+ch-48;
        ch=getchar();
    }
    return res*f;
}
輸出整數
void print(int x){
	if(x == 0) {putchar(48);return;}
	int len=0,dg[20];
	while(x>0){dg[++len]=x%10;x/=10;}
	for(int i=len ; i>=1 ; --i)putchar(dg[i]+48);
}
用法
int n = read();
print(n);
注意
不能跟ios::sync_with_stdio(false)混用

[++ , -- 放前面]
for(int i=0; i<=n; i++)   //slower
for(int i=0; i<=n; ++i)   //faster

[Inline、Const、傳參考(&)]
在簡單的函數前面加上 inline。
函數需要傳入參數的時候，在變數前面加上&取址符號，我們稱這個為傳參考。
加上 const 在變數前面，但這個變數在這個函數中就無法修改了。
inline void is_digit(const char &c)
    return (c>='0' && c<='9');

[Pragma GCC Optimize]
程式碼加上下面這行。
注意 : 如果程式碼里有遞迴的話，用O2會比O3快，因為O3優化會縮小堆疊空間。
#pragma GCC optimize("Ofast,fast-math,unroll-loops")

[No Long Long]
反正 long long 比 int慢很多。

[使用位元運算]
乘以或除以2的冪次可以用 << 和 >>
判斷奇數偶數可以用 & 如果 x&1 == 1 就表示 x 是奇數
判斷不等於可以把 a != b 改成 a ^ b

[圖論存圖用鏈式前向星]
就很快。不過聽說如果數據非常大的話(v=1e6,edge=4e6之類的)，vector反而會比較快

[減少記憶體使用量]
#include<bits/stdc++.h> → #include<stdio.h>
這檔案很大，你 include 它就要編譯它，會用很多記憶體。
using namespace std; → 自己寫std裡面的東西 ， 或是用到的時候才在前面加上std::

