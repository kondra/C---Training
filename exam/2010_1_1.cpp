#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
    int i;
public:
    A(int i) : i(i) {
    }
    A& operator*=(int x) {
        i *= x;
        return *this;
    }
    A& operator*=(A& a) {
        i *= a.i;
        a.i /= 2;
        return *this;
    }
    /*
    A operator*=(const A& a) {
        if (a.i == 10) {
            i *= a.i;
            return *this;
        }
        if (a.i == 2) {
            return A(i * a.i);
        }
        i *= a.i;
        return *this;
    }
    */
    int get() const {
        return i;
    }
};

int main()
{
    A a1(5), a2 = 3;
    a1 *= 10;
    a2 *= a1 *= 2;
    cout << a1.get() << ' ' << a2.get() << endl;
    return 0;
}
