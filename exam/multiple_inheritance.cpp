#include <iostream>

using namespace std;

class A {
public:
    A(const A&) {
        cout << "A(A&)" << endl;
    }
    A() {
        cout << "A()" << endl;
    }
};

class B {
public:
    B(const B&) {
        cout << "B(B&)" << endl;
    }
    B() {
        cout << "B()" << endl;
    }
};

class C : public A, public B {
public:
    C(const C&) {
        cout << "C(C&)" << endl;
    }
    C() {
        cout << "C()" << endl;
    }
};

int main()
{
    C c;
    B b = c;
    A a = c;
    return 0;
}
