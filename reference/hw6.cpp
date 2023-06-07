#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

class HugeInt{
private:
    short integer[40];

public:
    HugeInt(const string& s){
        memset(integer,0,sizeof(integer));
        for(int i=0;i<s.length();i++)
            integer[i]=s[s.length()-1-i]-'0';
    }

    HugeInt operator+(const HugeInt& other)const{
        HugeInt result("");
        for(int i=0;i<40;i++){
            result.integer[i]+=
                integer[i]+other.integer[i];
            if(result.integer[i]>=10){
                result.integer[i]-=10;
                result.integer[i+1]++;
            }
        }
        return result;
    }

    HugeInt operator-(const HugeInt& other)const{
        HugeInt result("");
        for(int i=0;i<40;i++){
            result.integer[i]+=
                integer[i]-other.integer[i];
            if(result.integer[i]<0){
                result.integer[i]+=10;
                result.integer[i+1]--;
            }
        }
        return result;
    }

    HugeInt operator*(const HugeInt& other)const{
        HugeInt result("");
        for(int i=0;i<40;i++)
            for(int j=0;j<40;j++)
                result.integer[i+j]+=
                    integer[i]*other.integer[j];
        for(int i=0;i<40;i++){
            result.integer[i+1]+=result.integer[i]/10;
            result.integer[i]%=10;
        }
        return result;
    }

    HugeInt operator/(const HugeInt& other)const{
        HugeInt result("");
        HugeInt remainder("0");
        HugeInt num("10");
        for(int i=39;i>=0;i--){
            if(i==39) remainder.integer[0]=integer[i];
            else{
                remainder=remainder*num;
                remainder.integer[0]=integer[i];
            }
            int quotient=0;
            while(remainder>other){
                remainder=remainder-other;
                quotient++;
            }
            if(remainder==other){
                remainder=remainder-other;
                quotient++;
            }
            result.integer[i]=quotient;
        }
        return result;
    }

    HugeInt operator%(const HugeInt& other)const{
        HugeInt remainder("0");
        HugeInt value("0");
        HugeInt num("10");
        for(int i=39;i>=0;i--){
            remainder=remainder*num;
            remainder.integer[0]=integer[i];
            while(remainder>other) 
                remainder=remainder-other;
            if(remainder==other) remainder=value;
        }
        return remainder;
    }
    
    bool operator>(const HugeInt& other)const{
        for(int i=39;i>=0;i--){
            if(integer[i]>other.integer[i]) 
                return true;
            else if(integer[i]<other.integer[i]) 
                return false;
        }
        return false;
    }
    bool operator<(const HugeInt& other)const{
        for(int i=39;i>=0;i--){
            if(integer[i]<other.integer[i]) 
                return true;
            else if(integer[i]>other.integer[i]) 
                return false;
        }
        return false;
    }
    bool operator==(const HugeInt& other)const{
        for(int i=39;i>=0;i--)
            if(integer[i]!=other.integer[i]) 
                return false;
        return true;
    }
    bool operator>=(const HugeInt& other)const{
        for(int i=39;i>=0;i--)
            if(integer[i]<other.integer[i]) 
                return false;
        return true;
    }
    bool operator<=(const HugeInt& other)const{
        for(int i=39;i>=0;i--)
            if(integer[i]>other.integer[i]) 
                return false;
        return true;
    }
    bool operator!=(const HugeInt& other)const{
        return !(*this==other);
    }
    friend istream& operator>>
        (istream& in,HugeInt& hugeInt){
        string s;
        in>>s;
        hugeInt=HugeInt(s);
        return in;
    }
    friend ostream& operator<<
        (ostream& out,const HugeInt& hugeInt){
        bool isLeadingZero=true;
        for(int i=39;i>=0;i--){
            if(hugeInt.integer[i]) 
                isLeadingZero=false;
            if(!isLeadingZero) 
                out<<hugeInt.integer[i];
        }
        if(isLeadingZero) out<<0;
        return out;
    }
    void print(HugeInt a,HugeInt b){
        if(a>b) cout<<a<<" > "<<b<<endl;
        else if(a<b) cout<<a<<" < "<<b<<endl;
        else cout<<a<<" = "<<b<<endl;
        cout<<a<<" + "<<b<<" = "<<a+b<<endl;
        if(a>b) cout<<a<<" - "<<b<<" = "<<a-b<<endl;
        else if(a<b) 
            cout<<a<<" - "<<b<<" = -"<<b-a<<endl;
        else cout<<a<<" - "<<b<<" = "<<a-b<<endl;
        cout<<a<<" * "<<b<<" = "<<a*b<<endl;
        cout<<a<<" / "<<b<<" = "<<a/b<<endl;
        cout<<a<<" % "<<b<<" = "<<a%b<<endl;
    }
};

int main(){
    string x,y;
    int cnt=0;
    while(cin>>x>>y){
        HugeInt x1(x);
        if(cnt++) cout<<endl;
        x1.print(x,y);
    }
}
