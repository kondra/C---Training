#include <iostream>

using namespace std;

template<unsigned long long n>
struct Factorial {
    static const unsigned long long f = n * Factorial<n - 1>::f;
};

template<>
struct Factorial<0> {
    static const unsigned long long f = 1;
};


int main()
{
    cout << Factorial<50>::f << endl;
    return 0;
}
