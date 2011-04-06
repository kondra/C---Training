#include <iostream>

using namespace std;

class Base
{
    virtual void _show() const = 0;

    int field;
public:
    virtual void show1() const = 0;

    void show() const {
        cout << "base" << endl;
        _show();
    }
};

class Derived : public Base
{
public:
    void _show() const {
        cout << "1" << endl;
    }
    void show1() const {
        cout << "derived show1" << endl;
        _show();
    }
};

int main()
{
    Derived d;
    Base& b = d;
    b.show();
    d.show1();
    return 0;
}
