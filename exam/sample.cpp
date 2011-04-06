#include <iostream>

using namespace std;

class A {
public:
    int i;
    A() {
        i = -1;
        cout << "A::A()\n";
    }
    A(const A& a) {
        i = a.i;
        cout << "A::A(const A&)\n";
    }
    ~A() {
        cout << "A::~A()\n";
    }
};

class B : public A {
public:
    int j;
    B() {
        j = -2;
        cout << "B::B()\n";
    }
    B(const B& b) : A(b) {
        j = b.j;
        cout << "B::B(const B&)\n";
    }
    ~B() {
        cout << "B::~B()\n";
    }
};

int main()
{
    B b;
    b.i = 1234;
    b.j = 12;
    B c(b);
    cout << c.i << endl;
    cout << c.j << endl;
    return 0;
}
