#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iterator>
#include <cctype>
#include <queue>

using namespace std;

class Automaton
{
    typedef map<char, set<unsigned int> > NodeInfo;

    string alphabet;
    unsigned int state_num;
    unsigned int final_state_num;
    unsigned int start_state;
    unsigned int err_state;

    bool dfa;

    set<unsigned int> start_states;
    set<unsigned int> final_states;
    vector<NodeInfo> transitions;
public:
    Automaton() : state_num(0), final_state_num(0), start_state(0), dfa(false) {
    }

    void convert_to_dfa();
    void reverse();

    friend ostream& operator<<(ostream& os, Automaton& g);
    friend istream& operator>>(istream& is, Automaton& g);
};

istream& operator>>(istream& is, Automaton& a) {
    unsigned int i, j, t;

    is >> a.alphabet;
    is >> a.state_num >> a.start_state >> a.final_state_num;
    a.transitions.resize(a.state_num);
    a.start_state--;
    for (i = 0; i < a.final_state_num; ++i) {
        is >> t;
        t--;
        a.final_states.insert(t);
    }
    for (i = 0; i < a.state_num; i++) {
        for (j = 0; j < a.alphabet.size(); j++) {
            cin >> t;
            a.transitions[i][a.alphabet[j]].insert(t - 1);
        }
    }
    return is;
}

ostream& operator<<(ostream& os, Automaton& a) {
    set<unsigned int>::const_iterator it;
    Automaton::NodeInfo::iterator n_it;

    unsigned int i, j;

//    os << a.alphabet << '\n';
    os << a.state_num << '\n' << a.start_state + 1 << ' ' << a.final_state_num << ' ';
    for (it = a.final_states.begin(); it != a.final_states.end(); ++it)
        os << *it + 1 << ' ';
    os << '\n';
    for (i = 0; i < a.transitions.size(); i++) {
        for (j = 0; j < a.alphabet.size(); j++) {
            if ((n_it = a.transitions[i].find(a.alphabet[j])) != a.transitions[i].end()) {
                os << *(n_it->second.begin()) + 1 << ' ';
            } else {
                os << a.err_state << ' ';
            }
        }
        os << '\n';
    }
    for (i = 0; i < a.alphabet.size(); i++) {
        os << a.err_state << ' ';
    }
    os << '\n';
    return os;
}

void Automaton::convert_to_dfa() {
    NodeInfo::iterator it;

    queue<unsigned int> new_states;
    set<unsigned int> old_states;
    map<set<unsigned int>, unsigned int> names;

    unsigned int i;
    unsigned int cur_state, state_cnt, next_node;

    if (dfa) return;

    state_cnt = transitions.size();

    if (start_states.size() == 1) {
        new_states.push(start_state);
    } else {
        names[start_states] = state_cnt;
        new_states.push(state_cnt);
        start_state = state_cnt;
        next_node = start_state;
        state_cnt++;

        set<unsigned int>::iterator s_it = start_states.begin();
        map<char, set<unsigned int> > tmp = transitions[*s_it];
        if (final_states.find(*s_it) != final_states.end())
            final_states.insert(next_node);
        s_it++;
        for (; s_it != start_states.end(); s_it++) {
            if (final_states.find(*s_it) != final_states.end())
                final_states.insert(next_node);
            for (NodeInfo::iterator m_it = transitions[*s_it].begin(); m_it != transitions[*s_it].end(); m_it++) {
                for (set<unsigned int>::iterator it = m_it->second.begin(); it != m_it->second.end(); it++) {
                    tmp[m_it->first].insert(*it);
                }
            }
        }

        transitions.push_back(tmp);
    }

    while (!new_states.empty()) {
        cur_state = new_states.front();
        new_states.pop();
        if (old_states.find(cur_state) != old_states.end())
            continue;

        for (i = 0; i < alphabet.size(); i++) {
            if ((it = transitions[cur_state].find(alphabet[i])) != transitions[cur_state].end()) {
                if (it->second.size() == 1) {
                    new_states.push(*(it->second.begin()));
                } else {
                    if (names.find(it->second) == names.end()) {
                        names[it->second] = state_cnt;
                        new_states.push(state_cnt);
                        next_node = state_cnt;
                        state_cnt++;

                        set<unsigned int>::iterator s_it = it->second.begin();
                        map<char, set<unsigned int> > tmp = transitions[*s_it];
                        if (final_states.find(*s_it) != final_states.end())
                            final_states.insert(next_node);
                        s_it++;
                        for (; s_it != it->second.end(); s_it++) {
                            if (final_states.find(*s_it) != final_states.end())
                                final_states.insert(next_node);
                            for (NodeInfo::iterator m_it = transitions[*s_it].begin(); m_it != transitions[*s_it].end(); m_it++) {
                                for (set<unsigned int>::iterator it = m_it->second.begin(); it != m_it->second.end(); it++) {
                                    tmp[m_it->first].insert(*it);
                                }
                            }
                        }

                        transitions[cur_state][alphabet[i]].clear();
                        transitions[cur_state][alphabet[i]].insert(next_node);
                        transitions.push_back(tmp);
                    } else {
                        next_node = names[it->second];
                        transitions[cur_state][alphabet[i]].clear();
                        transitions[cur_state][alphabet[i]].insert(next_node);
                    }
                }
            }
        }

        old_states.insert(cur_state);
    }

    state_num = state_cnt + 1;
    final_state_num = final_states.size();

    for (i = 0; i < transitions.size(); i++) {
        if (old_states.find(i) == old_states.end()) {
            transitions[i].clear();
        }
    }

    err_state = state_num;
}

void Automaton::reverse() {
    vector<NodeInfo> res;
    unsigned int i;

    res.resize(transitions.size());

    for (i = 0; i < transitions.size(); i++) {
        for (NodeInfo::iterator it = transitions[i].begin(); it != transitions[i].end(); it++) {
            res[*(it->second.begin())][it->first].insert(i);
        }
    }

    transitions = res;

    start_states = final_states;
    final_states.clear();
    final_states.insert(start_state);

    if (start_states.size() == 1) {
        start_state = *(start_states.begin());
    } else if (start_states.size() == 0) {
        transitions.clear();
        final_states.clear();
        final_state_num = 0;
        state_num = 1;
        err_state = 1;
        start_state = 0;
        dfa = true;
    }
}

int main()
{
    Automaton a;

    cin >> a;

    a.reverse();
    a.convert_to_dfa();

    cout << a;

    return 0;
}
