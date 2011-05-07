#include <iostream>
#include <cctype>
#include <iterator>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

class Grammar
{
    unsigned int max_len;
    string start_s;

    vector<pair<string, string> > rules;
public:
    Grammar() : max_len(0), start_s("S") {
    }

    friend ostream& operator<<(ostream& os, const Grammar& g);
    friend istream& operator>>(istream& is, Grammar& g);

    void remove_unproductive();
    void remove_inaccessible();
    void remove_eps_prod();
    void normalize();
};

ostream& operator<<(ostream& os, const Grammar& g) {
    vector<pair<string, string> >::const_iterator it;
    for (it = g.rules.begin(); it != g.rules.end(); ++it)
        os << it->first << ' ' << it->second << '\n';
    return os;
}

istream& operator>>(istream& is, Grammar& g) {
    istream_iterator<string> in(is);
    istream_iterator<string> all;
    pair<string, string> p;

    while (in != all) {
        p.first = *(in++);
        p.second = *(in++);
        if (p.second.size() > g.max_len)
            g.max_len = p.second.size();
        g.rules.push_back(p);
    }
    return is;
}

void Grammar::remove_unproductive() {
    vector<pair<string, string> > res;
    vector<pair<string, string> >::iterator it;
    set<string> v_set;
    set<string> v_set_prev;

    unsigned int i, j;
    bool flag;

    i = 0;
    while (true) {
        v_set_prev = v_set;
        for (it = rules.begin(); it != rules.end(); it++) {
            flag = true;
            for (j = 0; j < it->second.size(); j++) {
                if (!(it->second[j] == '_' || islower(it->second[j]) || isdigit(it->second[j]) ||
                            v_set_prev.find(string(1, it->second[j])) != v_set_prev.end())) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                v_set.insert(string(1, it->first[0]));
        }

        if (v_set_prev == v_set)
            break;
        i++;
    }

    for (it = rules.begin(); it != rules.end(); it++) {
        flag = true;
        for (j = 0; j < it->second.size(); j++) {
            if (!(it->second[j] == '_' || islower(it->second[j]) || isdigit(it->second[j]) ||
                        v_set.find(string(1, it->second[j])) != v_set.end())) {
                flag = false;
                break;
            }
        }
        if (flag && v_set.find(string(1, it->first[0])) != v_set.end())
            res.push_back(*it);
    }

    rules = res;
}

void Grammar::remove_inaccessible() {
    vector<pair<string, string> >::iterator it;
    vector<pair<string, string> > res;
    set<string> v_set;
    set<string> v_set_prev;

    unsigned int i, j;

    v_set_prev.insert(start_s);
    v_set.insert(start_s);

    i = 0;
    while (true) {
        v_set_prev = v_set;
        for (it = rules.begin(); it != rules.end(); it++) {
            if (v_set_prev.find(string(1, it->first[0])) != v_set_prev.end()) {
                for (j = 0; j < it->second.size(); j++) {
                    if (it->second[j] != '_') {
                        v_set.insert(string(1, it->second[j]));
                    }
                }
            }
        }
        if (v_set_prev == v_set)
            break;
        i++;
    }

    for (it = rules.begin(); it != rules.end(); it++) {
        if (v_set.find(string(1, it->first[0])) != v_set.end())
            res.push_back(*it);
    }

    rules = res;
}

void Grammar::normalize() {
    remove_unproductive();
    remove_inaccessible();
}

void Grammar::remove_eps_prod() {
    vector<pair<string, string> > res;
    vector<pair<string, string> >::iterator it;
    set<string> set_A;
    
    bool flag = false;
    unsigned int j, i;

    for (it = rules.begin(); it != rules.end(); it++) {
        if (it->second.length() == 1 && it->second[0] == '_') {
            set_A.insert(it->first);
        } else {
            res.push_back(*it);
        }
    }
    rules = res;

    do {
        flag = false;
        for (it = rules.begin(); it != rules.end(); ++it) {
            for (j = 0; j < it->second.size(); ++j) {
                if (set_A.find(string(1, it->second[j])) == set_A.end())
                    break;
            }
            if (j == it->second.size()) {
                if (set_A.insert(string(1, it->first[0])).second == true)
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
            if (set_A.find(string(1, rules[t].second[j])) != set_A.end())
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

    if (set_A.find("S") != set_A.end()) {
        rules.push_back(pair<string, string>("$", "S"));
        rules.push_back(pair<string, string>("$", "_"));
        start_s = "$";
    }

    vector<pair<string, string> >::iterator end;

    sort(rules.begin(), rules.end());
    end = unique(rules.begin(), rules.end());
    rules.erase(end, rules.end());

    normalize();
}

int main()
{
    Grammar g;

    cin >> g;
    g.remove_eps_prod();
    cout << g;

    return 0;
}
