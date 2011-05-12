//grammar on paper
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

long long summ();
long long expr();
long long mult();

vector<string> lexems;
vector<string>::iterator it;

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
    long long res = 0, tmp;
    res = mult();
    while (it != lexems.end()) {
        if (*it == "*") {
            it++;
            res *= mult();
        } else if (*it == "/") {
            it++;
            tmp = mult();
            if (tmp != 0) {
                res /= tmp;
            } else {
                throw(string("division by zero"));
            }
        } else if (*it == "%") {
            it++;
            tmp = mult();
            if (tmp != 0) {
                res %= tmp;
            } else {
                throw(string("division by zero"));
            }
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
    istream_iterator<string> in(cin);
    istream_iterator<string> end;

    copy(in, end, insert_iterator<vector<string> >(lexems, lexems.begin()));

    it = lexems.begin();

    try {
        long long res;
        res = expr();
        if (it != lexems.end()) {
            throw(string("bad lexems"));
        }
        cout << res << endl;
    } catch (const string& s) {
        cout << "ERROR " << s << endl;
    }

    return 0;
}
