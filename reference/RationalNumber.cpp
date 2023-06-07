#include<iostream>
#include<math.h>
#include<algorithm>
#include<vector>
#include<complex>
#include<iomanip>
using namespace std;

int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

class Rational{

public:
    int molecular,denominator;
    Rational(int m=1,int d=2){
        molecular=m;
        denominator=d;
    }

    friend ostream& operator<<(ostream& os, const Rational& r){
        if(r.molecular==0) os<<0;
        else if(r.molecular==1&&r.denominator==1) os<<1;
        else os<<"("<<r.molecular<<"/ "<<r.denominator<<")";
        return os;
    }

    friend istream& operator>>(istream& is, Rational& r){
        char slash;
        is>>r.molecular>>slash>>r.denominator;
        return is;
    }

    Rational operator+(const Rational& other){
        Rational result;
        result.molecular=molecular*other.denominator+other.molecular*denominator;
        result.denominator=denominator*other.denominator;
        int commonDivisor=gcd(result.molecular,result.denominator);
        result.molecular/=commonDivisor;
        result.denominator/=commonDivisor;
        return result;
    }

    Rational operator-(const Rational& other) {
        Rational result;
        result.molecular=molecular*other.denominator-other.molecular*denominator;
        result.denominator=denominator*other.denominator;
        int commonDivisor=gcd(result.molecular,result.denominator);
        result.molecular/=commonDivisor;
        result.denominator/=commonDivisor;
        return result;
    }

    Rational operator*(const Rational& other) {
        Rational result;
        result.molecular=molecular*other.molecular;
        result.denominator=denominator*other.denominator;
        int commonDivisor=gcd(result.molecular,result.denominator);
        result.molecular/=commonDivisor;
        result.denominator/=commonDivisor;
        return result;
    }

    Rational operator/(const Rational& other) {
        Rational result;
        result.molecular=molecular*other.denominator;
        result.denominator=denominator*other.molecular;
        int commonDivisor=gcd(result.molecular,result.denominator);
        result.molecular/=commonDivisor;
        result.denominator/=commonDivisor;
        return result;
    }
};

int main(){
    char op,g;
    Rational r1,r2;
    while(cin>>op){
        cin>>g>>r1>>g>>g>>r2>>g;
        if(r1.molecular%r1.denominator) cout<<r1;
        else cout<<r1.molecular/r1.denominator;
        cout<<" "<<op<<" ";
        if(r2.molecular%r2.denominator) cout<<r2;
        else cout<<r2.molecular/r2.denominator;
        cout<<" = ";
        switch(op){
            case '+':
                cout<<r1+r2<<endl;
                break;
            case '-':
                cout<<r1-r2<<endl;
                break;
            case '*':
                cout<<r1*r2<<endl;
                break;
            case '/':
                cout<<r1/r2<<endl;
                break;
        }
    }
    return 0;
}