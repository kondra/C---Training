#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
    int x;
public:
    A() : x(0) {
    }
    virtual void f() = 0;
};

struct B {
    double a;
    B operator++(int) {
        B tmp;
        tmp.a = a;
        a += 1.0;
        return tmp;
    }
    operator double() {
        return a;
    }
};

int main()
{
    B b, c;
    b.a = 1.0;
    b++;
    c = b++;
    double x;
    x = b;
    int y;
    y = b;
    cout << "c=" << c.a << endl;
    cout << "b=" << b.a << endl;
    return 0;
}
