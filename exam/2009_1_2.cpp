#include <iostream>

using namespace std;

class A {
public:
    virtual void f(int x) {
        h(x);
        cout << "A::f," << x << endl;
    }
    void g() {
        h(0);
        cout << "A::g" << endl;
    }
    virtual void h(int k) {
        cout << "A::h," << k << endl;
    }
};

class B : virtual public A {
public:
    void f(int y) {
        h(y);
        cout << "B::f," << y << endl;
    }
    void g() {
        h(1);
        cout << "B::g" << endl;
    }
    void h(int k) {
        cout << "B::h," << k << endl;
    }
};

int main()
{
    A a;
    B b;
    A *p = &b;
    p->f(2);
    p->g();
//    p->h();
    p->h(3);
    return 0;
}
