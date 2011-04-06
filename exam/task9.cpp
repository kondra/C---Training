#include <iostream>

using namespace std;

class X {
    int x;
public:
    X(int i) : x(i) {
    }
    operator int() {
        return x;
    }
};

void f(char *s) {
    cout << "f1\n";
}

//void f(const X& x, char *s) {
void f(int x, char *s) {
    cout << "f2\n";
}

int main()
{
    X x(1);
    int k;
    k = x;
    f("p");
    f(x, 0);
    f(0, 0);
    f(x, "q");
    f(1, "r");
    return 0;
}
