#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void f() {
}

class Y {
public:
    void f() {
    }
};

class X : public Y {
    double a;
    X(int k = 0) {
        a = k;
    }
public:
    X(double r) {
        a = r;
    }
    void f(int x) {
        a = x;
    }
    void f(int x, int y = 5) {
        a = x - y;
    }
    void g() {
//        f();
//        f(3);
        f(1, 2);
    }
};

int main()
{
    Y y;
//    X a;
    X b(2.5);
//    b.f();
    return 0;
}
