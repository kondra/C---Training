//grammar on paper
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

vector<string> lexems;
vector<string>::iterator it;

enum States {
    WAIT,
    NUMBER,
    OPERATION,
    BRACKET,
    END,
};

bool isoperation(char c) {
    if (c == '+' || c == '-' || c == '*')
        return true;
    return false;
}

void lexer(const string& str) {
    string tmp;

    unsigned int state, i;

    i = 0;
    state = WAIT;
    while (state != END) {
        if (state == WAIT) {
            if (isoperation(str[i])) {
                lexems.push_back(string(1, str[i]));
            } else if (isdigit(str[i])) {
                tmp.push_back(str[i]);
                state = NUMBER;
            } else if (str[i] == '.') {
                state = END;
            } else if (str[i] == '(' || str[i] == ')') {
                lexems.push_back(string(1, str[i]));
            }
            i++;
        } else if (state == NUMBER) {
            if (isspace(str[i])) {
                state = WAIT;
                lexems.push_back(tmp);
                tmp.clear();
            } else if (isoperation(str[i])) {
                state = WAIT;
                lexems.push_back(tmp);
                tmp.clear();
                lexems.push_back(string(1, str[i]));
            } else if (str[i] == '.') {
                state = END;
                lexems.push_back(tmp);
                tmp.clear();
            } else if (str[i] == '(' || str[i] == ')') {
                state = WAIT;
                lexems.push_back(tmp);
                tmp.clear();
                lexems.push_back(string(1, str[i]));
            } else if (isdigit(str[i])) {
                tmp.push_back(str[i]);
            }
            i++;
        }
    }
}

long long summ();
long long expr();
long long mult();

long long expr() {
    long long res = 0;
    res = summ();
    while (it != lexems.end()) {
        if (*it == "+") {
            it++;
            res += summ();
        } else if (*it == "-") {
            it++;
            res -= summ();
        } else {
            break;
        }
    }
    return res;
}

long long summ() {
    long long res = 0;
    res = mult();
    while (it != lexems.end()) {
        if (*it == "*") {
            it++;
            res *= mult();
        } else {
            break;
        }
    }
    return res;
}

long long mult() {
    long long res = 0;
    if (it != lexems.end()) {
        if (isdigit((*it)[0])) {
            istringstream(*it) >> res;
            it++;
        } else if (*it == "(") {
            it++;
            res = expr();
            if (it == lexems.end() || *it != ")") {
                throw(string("mult: unclosed bracket"));
            }
            it++;
        } else {
            throw("mult: failed on \"" + *it + "\"");
        }
    } else {
        throw(string("mult: no lexems"));
    }
    return res;
}

int main()
{
    string str;

    getline(cin, str);
    str.push_back('.');
    lexer(str);

    it = lexems.begin();

    try {
        long long res;
        res = expr();
        if (it != lexems.end()) {
            throw(string("bad lexems"));
        }
        cout << res << endl;
    } catch (const string& s) {
        cout << "WRONG" << endl;
    }

    return 0;
}
