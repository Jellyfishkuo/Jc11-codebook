說明
  atan() 和 atan2() 函數分別計算 x 和 y/x 的反正切。

回傳值
  atan() 函數會傳回介於範圍 -pi/2 到 pi/2 弧度之間的值。
  atan2() 函數會傳回介於 -pi 至 pi 弧度之間的值。
  如果 atan2() 函數的兩個引數都是零，
  則函數會將 errno 設為 EDOM，並傳回值 0。

範例
int main(void){
    double a,b,c,d;
    c=0.45;
    d=0.23;
    a=atan(c);
    b=atan2(c,d);
    printf("atan(%lf)=%lf/n",c,a);
    printf("atan2(%lf,%lf)=%lf/n",c,d,b);
 
}
// atan(0.450000)=0.422854
// atan2(0.450000,0.230000)=1.098299