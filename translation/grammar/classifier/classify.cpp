#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct IsUpper {
    bool operator()(char c) const {
        if (c >= 'A' && c <= 'Z')
            return true;
        return false;
    }
};

int main()
{
    vector<pair<string, string> > rules;
    vector<pair<string, string> >::iterator it = rules.begin();
    string::iterator st;

    //input
    istream_iterator<string> in(cin);
    istream_iterator<string> end;
    pair<string, string> p;

    while (in != end) {
        p.first = *(in++);
        p.second = *(in++);

        rules.push_back(p);
    }

    IsUpper is_up;

    //type3
    bool left_regular = true;
    bool right_regular = true; 

    for (it = rules.begin(); it != rules.end() && (left_regular || right_regular); it++) {
        if (it->first.size() == 1 && is_up(it->first[0])) {
            if (it->second.size() == 1)
                continue;
            if (is_up(it->second[0])) {
                st = find_if(it->second.begin() + 1, it->second.end(), is_up);
                if (st != it->second.end()) {
                    left_regular = right_regular = false;
                    break;
                }
                right_regular = false;
            } else if (is_up(it->second[it->second.size() - 1])) {
                st = find_if(it->second.begin(), it->second.end() - 1, is_up);
                if (st != it->second.end() - 1) {
                    left_regular = right_regular = false;
                    break;
                }
                left_regular = false;
           } else {
                st = find_if(it->second.begin(), it->second.end(), is_up);
                if (st != it->second.end()) {
                    left_regular = right_regular = false;
                    break;
                }
            }
        } else {
            left_regular = right_regular = false;
            break;
        }
    }

    if (left_regular) {
        cout << 3 << "\nleft-regular\n";
        return 0;
    }

    if (right_regular) {
        cout << 3 << "\nright-regular\n";
        return 0;
    }

    //type2
    bool left_non_terminals = true;

    it = rules.begin();
    for (it = rules.begin(); it != rules.end(); it++) {
        if (it->first.size() != 1 || !is_up(it->first[0])) {
            left_non_terminals = false;
            break;
        }
    }

    if (left_non_terminals) {
        cout << 2 << '\n';
        return 0;
    }
    //type1

    //S -> _
    bool right_S = false;
    bool left_S_eps = false;

    it = rules.begin();
    for (it = rules.begin(); it != rules.end(); it++) {
        if (it->second.find('S') != string::npos) {
            right_S = true;
        }
        if (it->first.size() == 1 && it->first[0] == 'S' &&
                it->second.size() == 1 && it->second[0] == '_') {
            left_S_eps = true;
        }
        if (it->first.size() == 1 && it->first[0] != 'S' &&
                it->second.size() == 1 && it->second[0] == '_') {
            cout << 0 << '\n';
            return 0;
        }
    }

    if (right_S && left_S_eps) {
        cout << 0 << '\n';
        return 0;
    }

    //non_shortened
    bool non_shortened = true;

    it = rules.begin();
    for (it = rules.begin(); it != rules.end(); it++) {
        if (it->first.size() > it->second.size()) {
            non_shortened = false;
            break;
        }
    }

    if (!non_shortened) {
        cout << 0 << '\n';
        return 0;
    }

    //context sensitive
    bool context_sens = true;

    
    for (it = rules.begin(); it != rules.end() && context_sens; it++) {
        if (it->second[0] == '_')
            continue;

        it->first.insert(0, "r");
        it->second.insert(0, "r");
        it->first.push_back('r');
        it->second.push_back('r');

        unsigned int sz = it->first.size() - 1;
        unsigned int sz2 = it->second.size() - 1;
        context_sens = false;
        for (unsigned int i = 0; i < sz && i < sz2 + 1; i++) {
            if (it->first[i] == it->second[i] && is_up(it->first[i + 1])) {
                context_sens = true;
                for (unsigned int j = 0; sz - j > i + 1; j++) {
                    if (it->first[sz - j] != it->second[sz2 - j]) {
                        context_sens = false;
                        break;
                    }
                }
                if (context_sens)
                    break;
            }
        }
    }

    if (context_sens) {
        cout << 1 << "\ncontext-sensitive\n";
        return 0;
    }

    if (non_shortened) {
        cout << 1 << "\nnon-shortened\n";
        return 0;
    }

    cout << 0 << '\n';

    return 0;
}
