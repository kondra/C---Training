#include <iostream>

using namespace std;

int x;

int f(int a) {
    cout << "::f\n";
    return x = a;
}

class A {
    int x;
public:
    A(int n = 1) {
        cout << "A\n";
        x = n;
    }
    int f(int a) {
        cout << "A::f(int)\n";
        return x = a;
    }
};

class B {
    int x;
public:
    B(int n = 2) {
        cout << "B\n";
        x = n;
    }
    virtual int f() {
        cout << "B::f()\n";
        return x = ::x;
    }
};

class C : public A, public B {
    int x;
public:
    C() {
        cout << "C\n";
    }
    int f(int a) {
        cout << "C:f(int)\n";
        return x = a;
    }
    int f() {
        cout << "C:f()\n";
        return x = ::x;
    }
};

/*
int main()
{
    A a; 
    B b; 
    C c;

    A *pa = &a;
    B *pb = &b;
    C *pc = &c;

    x = f(3);
//    x = pa->f();
    x = pa->f(4);

    pa = pc;
//    x = pa->f();
    x = pa->f(5);
    x = pb->f();
//    x = pb->f(6);

    pb = pc;
    x = pb->f();
//    x = pb->f(7);
    x = pc->f();
    x = pc->f(8);

    return 0;
}
*/

int main()
{
    struct D {
        A a;
        C c;
    };
    D d;
    return 0;
}
