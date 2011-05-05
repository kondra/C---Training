#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void process(vector<int>& v1, const vector<int>& v2, unsigned int k)
{
    vector<int>::const_iterator pv2 = v2.begin();
    vector<int>::iterator pv1 = v1.begin();

    for (; pv2 != v2.end(); pv2++) {
        if (*pv2 < 1 || static_cast<unsigned int>(*pv2) > v1.size())
            continue;
        *(pv1 + *pv2 - 1) *= k;
    }

    ostream_iterator<int> out_it(cout, " ");
    copy(v1.begin(), v1.end(), out_it);
}

/*
int main()
{
    vector<int> v1, v2;

    int i, tmp, n, m;
    cin >> n >> m;

    for (i = 0; i < n; i++) {
        cin >> tmp;
        v1.push_back(tmp);
    } 
    for (i = 0; i < m; i++) {
        cin >> tmp;
        v2.push_back(tmp);
    } 

    process(v1, v2, 2);
    cout << endl;

    return 0;
}
*/
