#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
public:
    static int x;
    A() {
    }
    int get_0() const {
        return x;
    }
};

int A::x;

int main()
{
    const A a;
    a.x = 1;
    a.get_0();
    return 0;
}
