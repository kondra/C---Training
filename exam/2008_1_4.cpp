#include <iostream>

using namespace std;

class X {
public:
    X() {
        cout << "X()\n";
    }
    X(const X&) {
        cout << "X(X&)\n";
    }
    ~X() {
        cout << "~X()\n";
    }
};

int i = 0;

class Z : public X {
    int id;
public:
    Z() {
        id = i++;
        cout << "Z() " << id << endl;
    }
    Z(const Z& z) : X(z) {
        id = 1000 + i++;
        cout << "Z(Z&) " << id << endl;
        cout << "dd " << z.id << endl;
    }
    ~Z() {
        cout << "~Z() " << id << endl;
    }
};

Z ret(Z& x, Z& y) {
    cout << "ret\n";
    return x;
}

int main()
{
    Z z;
    z = ret(z, z);
    cout << "return\n";
    return 0;
}
