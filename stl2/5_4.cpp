#include <vector>
#include <iterator>
#include <iostream>
#include <set>

using namespace std;

int main()
{
    vector<int> v;
    istream_iterator<int> it(cin);
    multiset<int> min_tree;
    multiset<int>::iterator st;
    int i, n, k;

    n = *it++;
    k = *it++;
    for (i = 0; i < n; it++, i++) {
        v.push_back(*it);
        if (i < k)
            min_tree.insert(*it);
    }

    for (i = 0; i + k < n; i++) {
        cout << *(min_tree.begin()) << endl;
        st = min_tree.find(v[i]);
        min_tree.erase(st);
        min_tree.insert(v[i + k]);
    }
    cout << *(min_tree.begin()) << endl;

    return 0;
}
