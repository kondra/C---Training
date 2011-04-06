#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
    int i;
public:
    A() : i(10) {
    }
    A(const A& a) {
        i = a.i + 10;
    }
    int get() const {
        return i;
    }
};

int main()
{
    A a1, a2 = a1, a3(a2);
    cout << a1.get() << ' ' << a2.get() << ' ' << a3.get() << endl;
    return 0;
}
