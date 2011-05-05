#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

//it's O(n+m) solution
//without vector of labels it would be O((n + m)logn) 
//because of sorting and binary search on each deletion
void process(const vector<int>& v, list<int>& l)
{
    int i, n;
    n = l.size();

    vector<int>::const_iterator pv;
    list<int>::iterator pl;
    vector<bool> label(n, false); //why shouldn't I use vector<bool> ?

    for (pv = v.begin(); pv != v.end(); pv++) {
        if (*pv > 0 && *pv <= n)
            label[*pv - 1] = true;
    }

    for (pl = l.begin(), i = 0; i < n; i++) {
        if (label[i])
            pl = l.erase(pl);
        else
            pl++;
    }
}

/*
int main()
{
    vector<int> v;
    list<int> l;

    int i, n, m;

    istream_iterator<int> it(cin);

    m = *it++;
    n = *it++;
    
    for (i = 0; i < m; i++)
        l.push_back(*it++);
    for (i = 0; i < n; i++)
        v.push_back(*it++);

    process(v, l);

    cout << endl;
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
*/
