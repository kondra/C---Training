#include <iostream>
#include <cctype>
#include <iterator>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    vector<pair<string, string> > rules;
    vector<pair<string, string> >::iterator it;

    set<char> set_A;

    //input
    istream_iterator<string> in(cin);
    istream_iterator<string> all;
    pair<string, string> p;

    unsigned int max_len = 0;

    while (in != all) {
        p.first = *(in++);
        p.second = *(in++);
        if (p.second[0] == '_') {
            set_A.insert(p.first[0]);
            continue;
        }
        if (p.second.size() > max_len)
            max_len = p.second.size();
        rules.push_back(p);
    }

    bool flag = false;
    unsigned int j, i;

    do {
        flag = false;
        for (it = rules.begin(); it != rules.end(); ++it) {
            for (j = 0; j < it->second.size(); ++j) {
                if (set_A.find(it->second[j]) == set_A.end())
                    break;
            }
            if (j == it->second.size()) {
                if (set_A.insert(it->first[0]).second == true)
                    flag = true;
            }
        }
    } while (flag);

    vector<int> pos(max_len);
    string tmp(max_len, '\0');
    unsigned int t, l, k, sz;
    sz = rules.size();

    for (t = 0; t < sz; ++t) {
        for (j = 0; j < max_len; ++j) {
            pos[j] = -1;
            tmp[j] = '\0';
        }

        for (i = j = 0; j < rules[t].second.size(); ++j) {
            if (set_A.find(rules[t].second[j]) != set_A.end())
                pos[j] = i++;
        }

        for (k = 0; k < 1u << i; ++k) {
            for (l = j = 0; j < rules[t].second.size(); ++j) {
                if (pos[j] == -1)
                    tmp[l++] = rules[t].second[j];
                else if (k & (1 << pos[j]))
                    tmp[l++] = rules[t].second[j];
            }
            if (l != 0)
                rules.push_back(pair<string, string>(rules[t].first, tmp.substr(0, l)));
        }
    }

    bool new_S = false;

    if (set_A.find('S') != set_A.end()) {
        rules.push_back(pair<string, string>("$", "S"));
        rules.push_back(pair<string, string>("$", "_"));
        new_S = true;
    }

    vector<pair<string, string> >::iterator end;

    sort(rules.begin(), rules.end());
    end = unique(rules.begin(), rules.end());
    rules.erase(end, rules.end());

    //remove_unuseful & ureachable
    vector<pair<string, string> > res;
    set<char> v_set;
    set<char> v_set_prev;

    i = 0;
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
            res.push_back(*it);
    }

    rules = res;

    res.clear();
    v_set.clear();
    v_set_prev.clear();

    if (new_S) {
        v_set_prev.insert('$');
        v_set.insert('$');
    } else {
        v_set_prev.insert('S');
        v_set.insert('S');
    }

    i = 0;
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
            res.push_back(*it);
    }

    rules = res;

    //output
    for (it = rules.begin(); it != rules.end(); ++it)
        cout << it->first << ' ' << it->second << '\n';

    return 0;
}
