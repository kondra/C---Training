#include <iostream>
#include <cctype>
#include <iterator>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main()
{
    vector<pair<string, string> > rules;
    vector<pair<string, string> >::iterator it;

    unsigned int i = 0, j;
    bool flag;

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

    while (true) {
        v_set_prev = v_set;
        for (it = rules.begin(); it != rules.end(); it++) {
            flag = true;
            for (j = 0; j < it->second.size(); j++) {
                if (!(it->second[j] == '_' || islower(it->second[j]) || isdigit(it->second[j]) ||
                        v_set_prev.find(it->second[j]) != v_set_prev.end())) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                v_set.insert(it->first[0]);
        }

        if (v_set_prev == v_set)
            break;
        i++;
    }

    for (it = rules.begin(); it != rules.end(); it++) {
        flag = true;
        for (j = 0; j < it->second.size(); j++) {
            if (!(it->second[j] == '_' || islower(it->second[j]) || isdigit(it->second[j]) ||
                    v_set.find(it->second[j]) != v_set.end())) {
                flag = false;
                break;
            }
        }
        if (flag && v_set.find(it->first[0]) != v_set.end())
            cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}
