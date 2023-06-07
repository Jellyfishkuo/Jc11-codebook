//分母為0
#include <iostream>
#include <exception>
using namespace std;
double divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw runtime_error("Division by zero!");
    }
    return static_cast<double> numerator/denominator;
}

int main() {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    try {
        double result = divide(a, b);
        cout << "Result: " << result << endl;
    } 
    catch (const exception& ex) {
        cout<<"Exception: "<<ex.what()<<endl;
    }
    return 0;
}

//自訂狀況類別以文字描述錯誤訊息
#include <iostream>
#include <exception>
using namespace std;
class MyException : public exception{
private:
    string errorMessage;
public:
    MyException(const string& message):
        errorMessage(message) {}
    const char* what() const throw(){
        return errorMessage.c_str();
    }
};
int main(){
    try{
        throw MyException("Custom exception occurred!");
    }
    catch (const MyException& ex){
        cout << "Exception: " << ex.what() << endl;
    }
    return 0;
}

//自訂狀況類別以代碼和文字描述錯誤訊息
#include <iostream>
#include <exception>
using namespace std;
class MyException : public exception{
private:
    int errorCode;
    string errorMessage;
public:
    MyException(int code, const string& message) 
        : errorCode(code), errorMessage(message) {}
    int getCode() const{
        return errorCode;
    }
    const char* what() const throw(){
        return errorMessage.c_str();
    }
};
int main(){
    try{
        throw MyException(404, "Page not found!");
    }
    catch (const MyException& ex){
        cout << "Exception: Error Code " 
            <<ex.getCode()<<" - "<<ex.what()<<endl;
    }
    return 0;
}

//自訂狀況類別使用更詳細的錯誤資訊
#include <iostream>
#include <exception>
using namespace std;
class MyException : public exception{
private:
    string fileName;
    int lineNumber;
    string errorMessage;
public:
    MyException(const string& file,
        int line, const string& message)
            : fileName(file), lineNumber(line),
                 errorMessage(message) {}

    const string& getFile() const{
        return fileName;
    }

    int getLine() const{
        return lineNumber;
    }

    const char* what() const throw(){
        return errorMessage.c_str();
    }
};
int main(){
    try{
        throw MyException(__FILE__, __LINE__,
            "Custom exception occurred!");
    }
    catch (const MyException& ex){
        cout << "Exception: " << ex.what() << endl;
        cout << "File: " << ex.getFile() << endl;
        cout << "Line: " << ex.getLine() << endl;
    }
    return 0;
}
