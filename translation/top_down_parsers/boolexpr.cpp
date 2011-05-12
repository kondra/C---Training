//grammar on paper
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

bool expr();
bool or_item();
bool xor_item();
bool and_item();

string str;
string::iterator it;

bool expr() {
    bool res = false;
    res = or_item();
    while (it != str.end()) {
        if (*it == '|') {
            it++;
            res |= or_item();
        } else {
            break;
        }
    }
    return res;
}

bool or_item() {
    bool res = false;
    res = xor_item();
    while (it != str.end()) {
        if (*it == '^') {
            it++;
            res ^= xor_item();
        } else {
            break;
        }
    }
    return res;
}

bool xor_item() {
    bool res = false;
    res = and_item();
    while (it != str.end()) {
        if (*it == '&') {
            it++;
            res &= and_item();
        } else {
            break;
        }
    }
    return res;
}

bool and_item() {
    bool res = false;
    if (it != str.end()) {
        if (isdigit(*it)) {
            res = *it - '0';
            it++;
        } else if (*it == '(') {
            it++;
            res = expr();
            if (it == str.end() || *it != ')') {
                throw(string("and_item: unclosed bracket"));
            }
            it++;
        } else if (*it == '!') {
            it++;
            res = and_item();
            res = !res;
        } else {
            throw("and_item: failed on \"" + string(1, *it) + "\"");
        }
    } else {
        throw(string("and_item: no str"));
    }
    return res;
}

int main()
{
    getline(cin, str);

    it = str.begin();

    try {
        bool res;
        res = expr();
        if (*it != '.') {
            throw(string("bad lexems"));
        }
        cout << res << endl;
    } catch (const string& s) {
        cout << "ERROR " << s << endl;
    }

    return 0;
}
