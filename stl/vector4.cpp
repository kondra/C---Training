#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

void process(const vector<int>& v, list<int>& l)
{
    int j;

    vector<int>::const_iterator pv = v.begin();
    list<int>::iterator pl;
    map<int, int>::iterator it;

    map<int, int> tmp;

    for (j = 1, pl = l.begin(); pl != l.end(); pl++, j++) {
        tmp.insert(pair<int, int>(j, *pl));
    }

    for (pv = v.begin(); pv != v.end(); pv++) {
        tmp.erase(*pv);
    }

    l.clear();
    for (it = tmp.begin(); it != tmp.end(); it++) {
        l.push_back((*it).second);
    }
}

/*
int main()
{
    vector<int> v;
    list<int> l;

    int i, tmp, n, m;
    cin >> n >> m;

    for (i = 0; i < n; i++) {
        cin >> tmp;
        v.push_back(tmp);
    } 
    for (i = 0; i < m; i++) {
        cin >> tmp;
        l.push_back(tmp);
    } 

    process(v, l);
    cout << endl;

    return 0;
}
*/
