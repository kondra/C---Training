#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void g(vector<int>& v) {
    vector<int>::reverse_iterator rt;

    int i, j;
    int n = v.size();
    for (j = i = 0; i < n; i++) {
        if (i % 2 == 0)
            continue;
        v.erase(v.begin() + i - j);
        j++;
    }

    for (rt = v.rbegin(); rt != v.rend(); rt++)
        cout << *rt << " ";
    cout << endl;
}

int main()
{
    vector<int> v;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<vector<int> >(v, v.begin()));
    g(v);
    return 0;
}
