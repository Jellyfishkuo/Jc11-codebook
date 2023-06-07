#include<iostream>
#include<iomanip>
#include<algorithm>
#include<math.h>
using namespace std;
class R {
    private:
        double area,diagonal;
    public:
        R(){};
        int length,width;
        R(double l,double w) {
            length=l;
            width=w;
        }
        int getA(){
            area=length*width;
            return area;
        }
        double getD(){
            diagonal=sqrt(length*length+width*width);
            return diagonal;
        }
};
bool cmp(R r1, R r2) {
    if(r1.getA() == r2.getA())
        return r1.getD()>r2.getD();
    return r1.getA()<r2.getA();
}
int main() {
    int n;
    cin>>n;
    R* r=new R[n];
    for(int i=0;i<n;i++) {
        int l,w;
        cin>>l>>w;
        r[i]=R(l,w);
    }
    sort(r,r+n,cmp);
    for(int i=0;i<n;i++){
        cout<<i+1<<":("<<r[i].length<<","<<r[i].width;
        cout<<") area= "<<r[i].getA();
        cout<<fixed<<setprecision(3)
            <<" diagonal= "<<r[i].getD()<<endl;
    }
    delete[] r;
    return 0;
}
