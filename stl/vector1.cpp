#include <iostream>
#include <vector>
#include <list>

using namespace std;

void process(const vector<int>& v, list<int>& l, int step)
{
    vector<int>::const_iterator vp = v.begin();
    list<int>::iterator lp = l.begin();
    list<int>::reverse_iterator lrp;

    if (l.size() == 0)
        return;

    while (lp != l.end() && vp < v.end()) {
        *lp = *vp;
        vp += step;
        lp++;
    }

    for (lrp = l.rbegin(); lrp != l.rend(); lrp++)
        cout << *lrp << " ";
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

    process(v, l, 100);
    cout << endl;

    return 0;
}
*/
