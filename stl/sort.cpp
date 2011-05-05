#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

inline int count(int x) {
    int i = 0;
    while (x > 0) {
        i += x & 1;
        x >>= 1;
    }
    return i;
}

inline bool compare(int x, int y) {
    int i, j;
    i = count(x);
    j = count(y);
    return i < j;
}

int main()
{
    vector<int> v;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<vector<int> >(v, v.begin()));

    stable_sort(v.begin(), v.end(), compare);

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\n"));

    return 0;
}
