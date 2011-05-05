#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    vector<int> v;
    istream_iterator<int> it(cin);
    int x, n, i, cnt;
    n = *it;
    it++;
    for (i = 0; i < n; it++, i++)
        v.push_back(*it);
    x = *it;
    cnt = count_if(v.begin(), v.end(), bind1st(equal_to<int>(), x));
    cout << cnt << endl;
    return 0;
}
