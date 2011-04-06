#include <iostream>

using namespace std;

class A {
public:
    A () {}
    static int i;
    static void f () {
        if (i >= 0)
            i = -1, g();
        cout << "f()" << endl;
    }
    static void g() {
        f();
        cout << "g()" << endl;
    }

//    friend A operator++(const A& a, int);
};

//A operator++ (const A& a, int) {
//    return A();
//}

int A::i = 1;

int main()
{
    A::i = 1;
    const A a;
    a.f();
    a.i = 0;
    return 0;
}
