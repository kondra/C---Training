#include <iostream>
#include <list>
#include <iterator>

using namespace std;

void g(list<int>& l) {
    list<int> tmp;
    list<int>::iterator it;
    list<int>::reverse_iterator rt;
    for (it = l.begin(); it != l.end(); it++)
        tmp.push_back(*it);
    l.clear();
    for (it = tmp.begin(); it != tmp.end(); it++) {
        l.push_back(*it);
        l.push_back(*it);
    }
    for (rt = l.rbegin(); rt != l.rend(); rt++)
        cout << *rt << " ";
    cout << endl;
}

int main()
{
    list<int> l;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<list<int> >(l, l.begin()));
    g(l);
    return 0;
}
