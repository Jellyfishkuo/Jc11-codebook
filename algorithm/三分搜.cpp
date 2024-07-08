  題意
給定兩射線方向和速度，問兩射線最近距離。
  題解
假設 F(t) 為兩射線在時間 t 的距離，F(t) 為二次函數，
可用三分搜找二次函數最小值。
struct Point{
    double x, y, z;
    Point() {}
    Point(double _x,double _y,double _z):
        x(_x),y(_y),z(_z){}
    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y >> p.z;
        return is;
    }
    Point operator+(const Point &rhs) const{
        return Point(x+rhs.x,y+rhs.y,z+rhs.z);
    }
    Point operator-(const Point &rhs) const{
        return Point(x-rhs.x,y-rhs.y,z-rhs.z);
    }
    Point operator*(const double &d) const{
        return Point(x*d,y*d,z*d);
    }
    Point operator/(const double &d) const{
        return Point(x/d,y/d,z/d);
    }
    double dist(const Point &rhs) const{
        double res = 0;
        res+=(x-rhs.x)*(x-rhs.x);
        res+=(y-rhs.y)*(y-rhs.y);
        res+=(z-rhs.z)*(z-rhs.z);
        return res;
    }
};
int main(){
    IOS;     //輸入優化
    int T;
    cin>>T;
    for(int ti=1;ti<=T;++ti){
        double time;
        Point x1,y1,d1,x2,y2,d2;
        cin>>time>>x1>>y1>>x2>>y2;
        d1=(y1-x1)/time;
        d2=(y2-x2)/time;
        double L=0,R=1e8,m1,m2,f1,f2;
        double ans = x1.dist(x2);
        while(abs(L-R)>1e-10){
            m1=(L+R)/2;
            m2=(m1+R)/2;
            f1=((d1*m1)+x1).dist((d2*m1)+x2);
            f2=((d1*m2)+x1).dist((d2*m2)+x2);
            ans = min(ans,min(f1,f2));
            if(f1<f2) R=m2;
            else L=m1;
        }
        cout<<"Case "<<ti<<": ";
        cout<<fixed<<setprecision(4)<<sqrt(ans)<<'\n';
    }
}