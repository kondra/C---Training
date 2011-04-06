#include <iostream>

using namespace std;

int& f(int n)
{
    int& t = *(new int [1]);
    t = n;
    return t;
}

int main()
{
    int j, n;
    unsigned int k;
    cin >> n;
    if (k < j) {
        cout << 1;
    }
    j = f(n);
    cout << ++j << endl;
    return 0;
}
