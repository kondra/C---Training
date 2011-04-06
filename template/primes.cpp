#include <iostream>

using namespace std;

template<int n, int i>
struct is_prime {
    enum { res = n % i && is_prime<n, i + 1>::res };
};

template<int n>
struct is_prime<n, n> {
    enum { res = 1 };
};

int main()
{
    cout << is_prime<7,2>::res << endl;
    return 0;
}
