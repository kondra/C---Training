#include <iostream>

using namespace std;

void g(int i, char *p=0) {
    cout << "g1\n";
}

void g(char x, char y) {
    cout << "g2\n";
}

void f(int x, int y) {

}

class B {
public:
    virtual void foo() {
        cout << "bar";
    }
};

int main()
{
    g(1);
    g('+', '+');
    g(2.3);
//    g(3, "str");
    f('+', 2);
    return 0;
}
