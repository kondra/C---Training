#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class C {
public:
    static const char c;
    static void f() {};
};

const char C::c = '+';

int main()
{
    C ob;
    C::f();
    ob.f();
    return 0;
}
