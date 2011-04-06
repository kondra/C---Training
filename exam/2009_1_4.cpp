#include <iostream>

using namespace std;

class A {
public:
    A() {
        cout << "A()\n";
    }
    A(const A&) {
        cout << "A(A&)\n";
    }
    ~A() {
        cout << "~A()\n";
    }
};

class B {
public:
    B() {
        cout << "B()\n";
    }
    B(const B&) {
        cout << "B(B&)\n";
    }
    ~B() {
        cout << "~B()\n";
    }
};

class C : public A, public B {
public:
    C() {
        cout << "C()\n";
    }
    C(const C& c) : A(c), B(c) {
        cout << "C(C&)\n";
    }
    ~C() {
        cout << "~C()\n";
    }
};

int main()
{
    C c;
    B b = c;
    A a = a;
    return 0;
}
