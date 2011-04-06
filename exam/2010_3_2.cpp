#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

float y = 0;

void f(float a) {
    y = a;
}

class T {
    int y;
public:
    void f() {
        y = 2;
    }
};

class S : public T {
public:
    void f(float n, float m) {
        ::y = n * m;
    }
    void f(char c1, char c2) {
        ::y = c1 + c2;
    }
    void g() {
//        f();
//        f(1);
//        f(-1, 1);
//        y = 2;
    }
};

int main()
{
    S b;
    f(5);
//    f('+', 6);
    b.g();
    return 0;
}
