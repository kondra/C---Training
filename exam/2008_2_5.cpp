#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void f(int x = 0, int y = 0) {
}

void f(const char *s) {
}

int main()
{
    f();
    f("abc");
    f(2);
    f('+', 3);
    return 0;
}
