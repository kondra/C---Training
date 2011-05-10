#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <queue>

using namespace std;

class Automaton;

class Grammar
{
    typedef vector<pair<string, string> > GRules;

    enum GrammarType {LEFT, RIGHT};

    GrammarType type;
    string start_s;
    unsigned int non_term_cnt;
    unsigned int max_len;

    bool filled;

    string alphabet;
    set<char> terminals;
    map<char, unsigned int> non_terminals;
    GRules rules;

    void add_non_term(const pair<string, string>& p);
    void set_update();
    void generate(pair<string, string> p, GRules& tmp);
    bool isterminal(char c);
public:
    Grammar() : start_s("S"), non_term_cnt(1), max_len(0), filled(false) { }

    void to_automaton_grammar();

    void remove_unproductive();
    void remove_inaccessible();
    void remove_eps_prod();
    void normalize();

    friend ostream& operator<<(ostream& os, const Grammar& g);
    friend istream& operator>>(istream& is, Grammar& g);
    friend class Automaton;
};

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
    set_update();
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
    set_update();
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

inline bool Grammar::isterminal(char c) {
    if (islower(c) || isdigit(c) || c == '_')
        return true;
    return false;
}

void Grammar::generate(pair<string, string> p, Grammar::GRules& tmp) {
    if (p.second.length() == 1 || (type == LEFT && p.second.length() == 2 && !isterminal(p.second[0]))) {
        tmp.push_back(p);
        return;
    }

    const int base = 0;
    const int range = 256;

    char new_nt = base + rand() % range;
    while (!isprint(new_nt) || new_nt == '$' || isterminal(new_nt) || non_terminals.find(new_nt) != non_terminals.end()) {
        new_nt = base + rand() % range;
    }

    non_terminals.insert(make_pair(new_nt, non_term_cnt++));
    if (type == LEFT) {
        tmp.push_back(make_pair(p.first, string(1, new_nt) + string(1, p.second[p.second.length() - 1])));
        generate(make_pair(string(1, new_nt), p.second.substr(0, p.second.length() - 1)), tmp);
    }
}

void Grammar::to_automaton_grammar() {
    GRules res, tmp;
    GRules::iterator it;

    unsigned int i, j;

    remove_eps_prod();
    cout << *this << endl;
    for (i = 0; i < rules.size(); i++) {
        if (rules[i].second.size() == 1 && !isterminal(rules[i].second[0])) {
            unsigned int sz = rules.size();
            for (j = 0; j < sz; j++) {
                if (rules[j].first[0] == rules[i].second[0] && rules[j].first[0] != rules[i].first[0]) {
                    rules.push_back(make_pair(rules[i].first, rules[j].second));
                }
            }
            rules.erase(rules.begin() + i);
            i--;
        } 
    }
    normalize();

    for (it = rules.begin(); it != rules.end(); it++) {
        if (it->second.size() >= 2) {
            generate(*it, tmp);
            res.insert(res.end(), tmp.begin(), tmp.end());
            tmp.clear();
        } else {
            res.push_back(*it);
        }
    }
    rules = res;
}

inline void Grammar::add_non_term(const pair<string, string>& p) {
    if (!isterminal(p.first[0])) {
        if (non_terminals.find(p.first[0]) == non_terminals.end()) {
            non_terminals.insert(make_pair(p.first[0], non_term_cnt++));
        }
    }
    for (unsigned int j = 0; j < p.second.length(); j++) {
        if (!isterminal(p.second[j])) {
            if (non_terminals.find(p.second[j]) == non_terminals.end()) {
                non_terminals.insert(make_pair(p.second[j], non_term_cnt++));
            }
        } else {
            if (!filled) {
                alphabet.push_back(p.second[j]);
            }
            terminals.insert(p.second[j]);
        }
    }
}

inline void Grammar::set_update() {
    GRules::const_iterator it;
    non_term_cnt = 1;
    non_terminals.clear();
    terminals.clear();
    for (it = rules.begin(); it != rules.end(); it++) {
        add_non_term(*it);
    }
}

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
        g.rules.push_back(p);
        g.add_non_term(p);
        if (p.second.size() > g.max_len)
            g.max_len = p.second.size();
    }
    g.type = Grammar::LEFT;
    g.filled = true;

    return is;
}

class Automaton
{
    typedef map<char, set<unsigned int> > NodeInfo;

    string alphabet;
    unsigned int state_num;
    unsigned int final_state_num;
    unsigned int start_state;
    unsigned int err_state;

    set<unsigned int> final_states;
    vector<NodeInfo> transitions;
public:
    Automaton() : state_num(0), final_state_num(0), start_state(0) { }
    Automaton(Grammar& g);

    void convert_to_dfa();
    void debug_print();

    friend ostream& operator<<(ostream& os, Automaton& g);
};

void Automaton::debug_print() {
    set<unsigned int>::const_iterator it;
    Automaton::NodeInfo::iterator n_it;

    unsigned int i, j;

    for (i = 0; i < transitions.size(); i++) {
        cout << "state " << i + 1 << '\n';
        for (j = 0; j < alphabet.size(); j++) {
            if ((n_it = transitions[i].find(alphabet[j])) != transitions[i].end()) {
                cout << "trans " << alphabet[j] << ": ";
                if (n_it->second.size() != 1) {
                    for (set<unsigned int>::iterator it = n_it->second.begin(); it != n_it->second.end(); it++) {
                        cout << *it + 1<< ' ';
                    }
                    cout << '\n';
                } else {
                    cout << *(n_it->second.begin()) + 1 << ' ';
                    cout << '\n';
                }
            }
        }
        cout << '\n';
    }
}

ostream& operator<<(ostream& os, Automaton& a) {
    set<unsigned int>::const_iterator it;
    Automaton::NodeInfo::iterator n_it;

    unsigned int i, j;

    os << a.alphabet << '\n';
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

    new_states.push(start_state);

    state_cnt = transitions.size();
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

Automaton::Automaton(Grammar& g) {
    if (g.rules.size() == 0) {
        state_num = 1;
        start_state = 0;
        final_state_num = 0;
        err_state = 0;
//        alphabet = "a";
        alphabet = g.alphabet;
        transitions.resize(1);
        return;
    }

    state_num = g.non_term_cnt + 1;
    start_state = 0;
    final_state_num = 1;
    if (g.type == Grammar::LEFT) {
        final_states.insert(g.non_terminals[g.start_s[0]]);
    }
    transitions.resize(state_num);
    err_state = state_num;

    for (set<char>::const_iterator it = g.terminals.begin(); it != g.terminals.end(); it++) {
        if (*it != '_')
            alphabet.push_back(*it);
    }

    for (vector<pair<string, string> >::const_iterator it = g.rules.begin(); it != g.rules.end(); it++) {
        if (g.type == Grammar::LEFT) {
            if (it->second.length() == 1) {
                if (it->second[0] == '_' && it->first == g.start_s) {
                    final_state_num++;
                    final_states.insert(0);
                    continue;
                }
                transitions[start_state][it->second[0]].insert(g.non_terminals[it->first[0]]);
            } else {
                transitions[g.non_terminals[it->second[0]]][it->second[1]].insert(g.non_terminals[it->first[0]]);
            }
        }
    }
}

int main()
{
    Grammar g;

    cin >> g;
    g.to_automaton_grammar();

    cout << "##\n";
    cout << g;
    cout << "##\n";

    Automaton a(g);
    a.convert_to_dfa();
    a.debug_print();
    cout << a;

    return 0;
}
