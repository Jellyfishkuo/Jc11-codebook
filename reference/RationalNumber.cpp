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
    int mol,den;
    Rational(int m=1,int d=2){
        mol=m;
        den=d;
    }

    friend ostream& operator<<(ostream& os, const Rational& r){
        if(r.mol==0) os<<0;
        else if(r.mol==1&&r.den==1) os<<1;
        else os<<"("<<r.mol<<"/ "<<r.den<<")";
        return os;
    }

    friend istream& operator>>(istream& is, Rational& r){
        char slash;
        is>>r.mol>>slash>>r.den;
        return is;
    }

    Rational operator+(const Rational& other){
        Rational result;
        result.mol=mol*other.den+other.mol*den;
        result.den=den*other.den;
        int com=gcd(result.mol,result.den);
        result.mol/=com;
        result.den/=com;
        return result;
    }

    Rational operator-(const Rational& other) {
        Rational result;
        result.mol=mol*other.den-other.mol*den;
        result.den=den*other.den;
        int com=gcd(result.mol,result.den);
        result.mol/=com;
        result.den/=com;
        return result;
    }

    Rational operator*(const Rational& other) {
        Rational result;
        result.mol=mol*other.mol;
        result.den=den*other.den;
        int com=gcd(result.mol,result.den);
        result.mol/=com;
        result.den/=com;
        return result;
    }

    Rational operator/(const Rational& other) {
        Rational result;
        result.mol=mol*other.den;
        result.den=den*other.mol;
        int com=gcd(result.mol,result.den);
        result.mol/=com;
        result.den/=com;
        return result;
    }
};

int main(){
    char op,g;
    Rational r1,r2;
    while(cin>>op){
        cin>>g>>r1>>g>>g>>r2>>g;
        if(r1.mol%r1.den) cout<<r1;
        else cout<<r1.mol/r1.den;
        cout<<" "<<op<<" ";
        if(r2.mol%r2.den) cout<<r2;
        else cout<<r2.mol/r2.den;
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