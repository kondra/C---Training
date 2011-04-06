#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Cls {
    int i;
    Cls& operator=(Cls&);
public:
    Cls() {
        i = 1;
    }
};

void f(Cls *p, Cls *q) {
    *p = *q;
}

int main()
{
    return 0;
}
