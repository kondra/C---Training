#include <iostream>
#include <cctype>
#include <iterator>
#include <vector>
#include <string>
#include <set>

using namespace std;

void input(vector<pair<string, string> >& rules) {
    vector<pair<string, string> >::iterator it;

    istream_iterator<string> in(cin);
    istream_iterator<string> end;
    pair<string, string> p;

    while (in != end) {
        p.first = *(in++);
        p.second = *(in++);
        rules.push_back(p);
    }
}

void output(vector<pair<string, string> >& rules) {
    vector<pair<string, string> >::iterator it;

    for (it = rules.begin(); it != rules.end(); it++)
        cout << it->first << ' ' << it->second << '\n';
}

void remove_unuseful(vector<pair<string, string> >& rules) {
    vector<pair<string, string> >::iterator it;

    set<char> v_set;
    set<char> v_set_prev;

    unsigned int i = 0, j;
    bool flag;

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

    vector<pair<string, string> > res;

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
            res.push_back(*it);
    }

    rules = res;
}

void remove_unreachable(vector<pair<string, string> >& rules) {
    vector<pair<string, string> >::iterator it;

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

    vector<pair<string, string> > res;

    for (it = rules.begin(); it != rules.end(); it++) {
        if (v_set.find(it->first[0]) != v_set.end())
            res.push_back(*it);
    }

    rules = res;
}

int main()
{
    vector<pair<string, string> > rules;

    input(rules);
    remove_unuseful(rules);
    remove_unreachable(rules);
    output(rules);

    return 0;
}
