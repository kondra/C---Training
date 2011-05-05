#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<class T>
void myswap(T& x, T& y)
{
    T t;
    t = x;
    x = y;
    y = t;
}

template<class T>
void myreverse(T begin, T end)
{
    T l, r;

    if (begin >= end)
        return;

    l = begin;
    r = end - 1;
    while (l < r) {
        myswap(*l, *r);
        l++;
        r--;
    }
}

/*
int main()
{
    vector<int> v;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<vector<int> >(v, v.begin()));

    myreverse(v.begin(), v.end());

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

    cout << endl;

    return 0;
}
*/
