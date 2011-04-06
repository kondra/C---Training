#include <iostream>

using namespace std;

class C {
public:
    virtual void f(int x) {
        h(x);
        cout << "C::f," << x << endl;
    }
    virtual void g() {
        h(0);
        cout << "C::g" << endl;
    }
    virtual void h() {
        cout << "C::h" << endl;
    }
    virtual void h(int k) {
        h();
        cout << "C::h," << k << endl;
    }
};

class D : public C {
public:
    virtual void f(int y) {
        h(y);
        cout << "D::f," << y << endl;
    }
    virtual void g() {
        h(1);
        cout << "D::g" << endl;
    }
    virtual void h() {
        cout << "D::h" << endl;
    }
    virtual void h(int k) {
        h();
        cout << "D::h," << k << endl;
    }
};

int main()
{
    C c;
    D d;
    C *p = &d;
    p->f(2);
    p->g();
    p->h();
    p->h(3);
    return 0;
}
