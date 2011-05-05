#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void process(vector<int>& v)
{
    vector<int> tmp;

    copy(v.begin(), v.end(), insert_iterator<vector<int> >(tmp, tmp.begin()));

    bool parity;
    vector<int>::iterator it = tmp.begin();
    v.clear();
    for (parity = true; it < tmp.end(); it++, parity = !parity) {
        if (!parity)
            v.push_back(*it);
    }

    copy(v.rbegin(), v.rend(), ostream_iterator<int>(cout, " "));
}

/*
int main()
{
    vector<int> v;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<vector<int> >(v, v.begin()));

    process(v);

    return 0;
}
*/
