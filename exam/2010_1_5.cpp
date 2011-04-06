#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
    int i;
public:
    A(int x) {
        i = x;
        cout << "first\n";
    }
    virtual ~A() {
        cout << "second\n";
    }
    int f() const {
        return i + g() + h();
    }
    virtual int g() const {
        return i;
    }
    int h() const {
        return 39;
    }
};

class B : public A {
public:
    B() : A(70) {
        cout << "third\n";
    }
    ~B() {
        cout << "fourth\n";
    }
    int f() const {
        return g() - 2;
    }
    virtual int g() const {
        return 4;
    }
    int h() const {
        return 6;
    }
};

int main()
{
    B b;
    A *p = &b;
    cout << p->f() << ", " << b.f() << endl;
    return 0;
}
