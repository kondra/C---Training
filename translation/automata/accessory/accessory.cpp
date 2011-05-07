#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class Automaton
{
    string alphabet;
    unsigned int state_num;
    unsigned int final_state_num;
    unsigned int start_state;

    set<unsigned int> final_states;
    map<pair<unsigned int, char>, unsigned int> transitions;
public:
    friend ostream& operator<<(ostream& os, const Automaton& g);
    friend istream& operator>>(istream& is, Automaton& g);

    bool check_belonging(string& str) const;
};

ostream& operator<<(ostream& os, const Automaton& a) {
    return os;
}

istream& operator>>(istream& is, Automaton& a) {
    unsigned int i, j, t;

    is >> a.alphabet;
    is >> a.state_num >> a.start_state >> a.final_state_num;
    a.start_state--;
    for (i = 0; i < a.final_state_num; ++i) {
        is >> t;
        t--;
        a.final_states.insert(t);
    }
    for (i = 0; i < a.state_num; i++) {
        for (j = 0; j < a.alphabet.size(); j++) {
            cin >> t;
            a.transitions[make_pair(i, a.alphabet[j])] = t - 1;
        }
    }
    return is;
}

bool Automaton::check_belonging(string& str) const {
    unsigned int i;
    unsigned int cur_state = start_state;

    map<pair<unsigned int, char>, unsigned int>::const_iterator it;

    for (i = 0; i < str.length(); i++) {
        if ((it = transitions.find(make_pair(cur_state, str[i]))) != transitions.end()) {
            cur_state = it->second;
        } else {
            return false;
        }
    }
    if (final_states.find(cur_state) != final_states.end())
        return true;
    return false;
}

int main()
{
    Automaton a;
    string str;

    bool result;

    cin >> str >> a;
    result = a.check_belonging(str);

    if (result)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
