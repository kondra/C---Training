#include <iostream>

using namespace std;

class C {
public:
//    int a;
    static  char c;
    static void f() {
    }
    void g() {}
};

 char C::c = '+';
/*
class X {
    int a;
public:
    X(int k) : a(k*2) {}
    static void g() {
        return;
    }
    void h() const {
        return;
    }
};

class C {
    int x;
public:
    C(int x) : x(x * 2) {}
    C operator+ (const C& c) {
        C tmp(0);
        tmp.x = x * 2 + c.x * 2;
        return tmp;
    }
    int get() const {
        return x;
    }
};
*/

int main()
{
 //   C c1(7), c2 = 5, c3(c1 + c2 + c1);
 //  cout << c1.get() << ' '<< c2.get() << ' ' << c3.get() << endl;
//
    C ob;
    C::f();
    ob.c=1;
    ob.f();
//
//    const X x(2);
//    X::g();
//    x.h();
    return 0;
}
