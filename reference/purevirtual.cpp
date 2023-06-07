#include <iostream>
using namespace std;
class Shape{
public:
    virtual double getArea() const=0;
};
class Circle:public Shape{
private:
    double radius;
public:
    Circle(double r):radius(r) {}
    double getArea() const override {
        return 3.14159*radius*radius;
    }
};
class Rectangle:public Shape{
private:
    double length;
    double width;
public:
    Rectangle(double l,double w):
            length(l),width(w) {}
    double getArea() const override{
        return length * width;
    }
};
int main() {
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    cout<<circle.getArea()<<endl;
    cout<<rectangle.getArea()<<endl;
    return 0;
}
