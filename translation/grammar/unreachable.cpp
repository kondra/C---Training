#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main()
{
    vector<pair<string, string> > rules;
    vector<pair<string, string> >::iterator it;

    //input
    istream_iterator<string> in(cin);
    istream_iterator<string> end;
    pair<string, string> p;

    while (in != end) {
        p.first = *(in++);
        p.second = *(in++);
        rules.push_back(p);
    }

    set<char> v_set;
    set<char> v_set_prev;

    v_set_prev.insert('S');
    v_set.insert('S');

    unsigned int i = 0, j;

    while (true) {
        v_set_prev = v_set;
        for (it = rules.begin(); it != rules.end(); it++) {
            if (v_set_prev.find(it->first[0]) != v_set_prev.end()) {
                for (j = 0; j < it->second.size(); j++) {
                    if (it->second[j] != '_') {
                        v_set.insert(it->second[j]);
                    }
                }
            }
        }
        if (v_set_prev == v_set)
            break;
        i++;
    }

    for (it = rules.begin(); it != rules.end(); it++) {
        if (v_set.find(it->first[0]) != v_set.end())
            cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}
