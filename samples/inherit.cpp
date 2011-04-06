#include <iostream>

using namespace std;

class Base
{
protected:
    int count;
public:
    Base() : count(0) {}
    int& setter() {
        return count;
    }
    const int& getter() const {
        return count;
    }
};

class Deriv1 : virtual public Base
{
};

class Deriv2 : virtual public Base
{
};

class MDeriv : public Deriv1, public Deriv2
{
};

int main(void)
{
    Deriv1 d1;
    d1.setter() = 1;

    cout << d1.getter() << endl;

    Deriv2 d2;
    d2.setter() = 2;
    cout << d2.getter() << endl;

    MDeriv md;
    md.setter() = 5;
    cout << md.getter() << endl;

    const Deriv1 cd1;
    cout << cd1.getter() << endl;
    int p;
    p = cd1.getter();
//    cd1.getter() = 5;

    return 0;
}
