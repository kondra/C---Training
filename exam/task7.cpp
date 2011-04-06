#include <iostream>

using namespace std;

struct mystr {
    int a, b;
    mystr() {}
private:
    mystr(const mystr&) {}
};

int i = sizeof(mystr);

int f(mystr s) {
    return 0;
}

int main()
{
    mystr s;
    f(s);
    return 0;
}
