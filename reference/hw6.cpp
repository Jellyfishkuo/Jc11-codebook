#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

class HugeInt
{
private:
    short integer[40];
public:
    HugeInt(const string& s){
        memset(integer, 0, sizeof(integer));
        int len = s.length();
        for (int i = 0; i < len; i++){
            integer[i] = s[len - 1 - i] - '0';
        }
    }

    HugeInt operator+(const HugeInt& other) const
    {
        HugeInt result("");
        for (int i = 0; i < 40; i++){
            result.integer[i] += integer[i] + other.integer[i];
            if (result.integer[i] >= 10){
                result.integer[i] -= 10;
                result.integer[i + 1] += 1;
            }
        }
        return result;
    }
    HugeInt operator-(const HugeInt& other) const{
        HugeInt result("");
        HugeInt num1("");
        HugeInt num2("");
        for(int i =0; i<40; i++){
            num1.integer[i] = num1.integer[i] + integer[i];
            num2.integer[i] = num2.integer[i] + other.integer[i];
        }
        if(num1 > num2){
            for (int i = 0; i < 40; i++){
                result.integer[i] += integer[i] - other.integer[i];
                if (result.integer[i] < 0){
                    result.integer[i] += 10;
                    result.integer[i + 1] -= 1;
                }
            }
        }
        else
        {
            for (int i = 0; i <= 39; i++){
                result.integer[i] += other.integer[i] - integer[i];
                if (result.integer[i] < 0){
                    result.integer[i] += 10;
                    result.integer[i + 1] -= 1;
                }
            }
        }
        return result;
    }
    HugeInt operator*(const HugeInt& other) const{
        HugeInt result("");
        for (int i = 0; i < 40; i++){
            for (int j = 0; j < 40; j++){
                result.integer[i + j] += integer[i] * other.integer[j];
            }
        }
        for (int i = 0; i <= 39; i++){
            result.integer[i + 1] += result.integer[i] / 10;
            result.integer[i] %= 10;
        }
        return result;
    }
    HugeInt operator/(const HugeInt& other) const{
        HugeInt result("");
        HugeInt remainder("0");
        HugeInt one("1");
        HugeInt num("10");
        for (int i = 39; i >= 0; i--){
            if(i == 39)
                remainder.integer[0] = integer[i];
            else{
                remainder = remainder * num;
                remainder.integer[0] = integer[i];
            }
            int quotient = 0;
            if(remainder > other){
                while (remainder > other){
                    remainder = remainder - other;
                    quotient++;
                }
            }
            if(remainder == other){
                remainder = remainder - other;
                quotient ++;
            }
            result.integer[i] = quotient;
        }
        return result;
    }
    HugeInt operator%(const HugeInt& other) const{
        HugeInt remainder("0");
        HugeInt value("0");
        HugeInt num("10");
        for (int i = 39; i >= 0; i--){
            remainder = remainder * num;
            remainder.integer[0] = integer[i];
            if(remainder > other){
                while (remainder > other){
                    remainder = remainder - other;
                }
            }
            if(remainder == other)
                remainder = value;
        }
        return remainder;
    }
    bool operator>(const HugeInt& other) const{
        for (int i = 39; i >= 0; i--){
            if (integer[i] > other.integer[i]){
                return true;
            }
            else if (integer[i] < other.integer[i]){
                return false;
            }
        }
        return false;
    }
    bool operator<(const HugeInt& other) const{
        for (int i = 39; i >= 0; i--){
            if (integer[i] < other.integer[i]){
                return true;
            }
            else if (integer[i] > other.integer[i]){
                return false;
            }
        }
        return false;
    }
    bool operator==(const HugeInt& other) const{
        for (int i = 39; i >= 0; i--){
            if (integer[i] != other.integer[i]){
                return false;
            }
        }
        return true;
    }
    bool operator>=(const HugeInt& other) const{
        for (int i = 39; i >= 0; i--){
            if (integer[i] < other.integer[i]){
                return false;
            }
        }
        return true;
    }
    bool operator<=(const HugeInt& other) const{
        for (int i = 39; i >= 0; i--){
            if (integer[i] > other.integer[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const HugeInt& other) const{
        return !(*this == other);
    }
    friend istream& operator>>(istream& in, HugeInt& hugeInt){
        string s;
        in >> s;
        hugeInt = HugeInt(s);
        return in;
    }

    friend ostream& operator<<(ostream& out, const HugeInt& hugeInt){
        bool isLeadingZero = true;
        for (int i = 39; i >= 0; i--){
            if (hugeInt.integer[i] != 0){
                isLeadingZero = false;
            }
            if (!isLeadingZero){
                out << hugeInt.integer[i];
            }
        }
        if (isLeadingZero){
            out << 0;
        }
        return out;
    }
};

int main()
{
    string x,y;
    int a =0;
    while(cin >> x >> y){
        HugeInt x1(x);
        HugeInt y1(y);
        if (x1 > y1){
            if(a != 0)
                cout << "\n";
            cout << x << " > " << y << endl;
        }
        else if (x1 < y1){
            if(a != 0)
                cout << "\n";
            cout << x << " < " << y << endl;
        }
        else{
            if(a != 0)
                cout << "\n";
            cout << x << " = " << y << endl;
        }
        HugeInt z = x1 + y1;
        if(x1 < y1){
            cout << x << " + " << y << " = " << z << endl;
            z = x1 - y1;
            cout << x << " - " << y << " = -" << z << endl;
            z = x1 * y1;
            cout << x << " * " << y << " = " << z << endl;
            z = x1 / y1;
            cout << x << " / " << y << " = " << z << endl;
            z = x1 % y1;
            cout << x << " % " << y << " = " << z << endl;
        }
        else{
            cout << x << " + " << y << " = " << z << endl;
            z = x1 - y1;
            cout << x << " - " << y << " = " << z << endl;
            z = x1 * y1;
            cout << x << " * " << y << " = " << z << endl;
            z = x1 / y1;
            cout << x << " / " << y << " = " << z << endl;
            z = x1 % y1;
            cout << x << " % " << y << " = " << z << endl;
        }
        a++;
    }
    return 0;
}
