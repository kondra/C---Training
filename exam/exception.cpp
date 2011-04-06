#include <iostream>

using namespace std;

struct X {
    X() {
        cout << "X()\n";
    }
    ~X() {
        cout << "~X()\n";
    }
    X(X&) {
        cout << "X(X&)\n";
    }
};

int main()
{
    try {
        try {
            X x;
            throw x;
        }
        catch (const X& x) {
            cout << "1\n";
            throw;
        }
    }
    catch (X) {
        cout << "2\n";
    }
    return 0;
}
