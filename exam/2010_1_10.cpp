#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Ex {
    int code;
public:
    Ex(int i) : code(i) {
    }
    Ex(const Ex& ex) : code(ex.code) {
    }
    int Get() const {
        return code;
    }
};

struct Ex90 : Ex {
    Ex90() : Ex(90) {
    }
};

void f() {
    throw Ex90();
    cout << "dog\n";
}

void t() {
    try {
        f();
    }
    catch (Ex90& x) {
        cout << "cat\n";
        throw Ex(x.Get() + 1);
        cout << "sheep\n";
    }
    catch (Ex&) {
        cout << "horse\n";
    }
    cout << "cow\n";
}

int main()
{
    try {
        t();
    }
    catch (Ex& x) {
        cout << "elephant " << x.Get() << endl;
    }
    catch (...) {
        cout << "wolf\n";
    }
    return 0;
}
