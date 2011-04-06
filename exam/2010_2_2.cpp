#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

double a = 0;

void f(double x = 2) {
    a = x;
}

void f() {
    a = 1;
}

struct B {
    double a;
    void f() {
        a = 2;
    }
};

class D : B {
public:
    void f(int a) {
        ::a = a;
    }
    void h() {
        f('r');
//        f();
        a = 2;
    }
};

int main()
{
    D d;
//    f();
    f(6);
    d.h();
    return 0;
}
