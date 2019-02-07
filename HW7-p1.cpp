#include <iostream>
using namespace std;

class Figure{
public:
    virtual void erase();
    virtual void draw();
    virtual void center();
private:

};

class Triangle : public Figure{
public:
    void erase(){cout << "Derived class Triangle object calling erase()." <<endl;}
    void draw(){cout << "Derived class Triangle object calling draw()." <<endl;}
    void center(){cout << "Derived class Triangle object calling center()." <<endl; erase(),draw();}
};

class Rectangle : public Figure{
public:
    void erase(){cout << "Derived class Rectangle object calling erase()." <<endl;}
    void draw(){cout << "Derived class Rectangle object calling draw()." <<endl;}
    void center(){cout << "Derived class Rectangle object calling center()." <<endl; erase(),draw();}
};



int main() {

    Triangle tri;
    tri.draw();
    cout << "n\Derived class Triangle object calling center().\n";
    tri.center();

    Rectangle rect;
    rect.draw();
    cout << "n\Derived class Rectangle object calling center().\n";
    rect.center();

    return 0;
}