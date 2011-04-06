#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int x = 0;

void f(int a, int b) {
    x = a + b;
}

class A {
    int x;
public:
    void f() {
        x = 2;
    }
    void f(char a1, char b1) {
        x = a1 - b1;
    }
};

class B : public A {
public:
    void f(int a) {
        ::x = a;
    }
    void g() {
//        f();
        f(0);
//        f(5.3, 1);
//        x = 1;
    }
};

int main()
{
    B b;
//    f(2);
    f(3, 'a');
    b.g();
    return 0;
}
