#include <iostream>

using namespace std;

class X {
    int i;
public:
    X(int i = 0) : i(i) {
    }
    X& operator++() {
        i++;
        return *this;
    }
    const int& getter() {
        return i;
    }
};

int main()
{
    X x;
    ++x;
    ++x;
    cout << x.getter() << endl;
    return 0;
}
