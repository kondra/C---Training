// can I show you a grammar tomorrow?
#include <iostream>
#include <list>
#include <utility>

using namespace std;

enum States {
    WAIT,
    NUMBER,
    OPERATION,
    BRACKET,
    END,
};

bool isoperation(char c) {
    if (c == '+' || c == '-' || c == '/' || c == '%' || c == '*')
        return true;
    return false;
}

int main()
{
    string str, tmp;
    list<pair<States, string> > lexems;
    list<pair<States, string> >::iterator it;

    unsigned int state, i;

    getline(cin, str);

    i = 0;
    state = WAIT;
    while (state != END) {
        if (state == WAIT) {
            if (isoperation(str[i])) {
                lexems.push_back(make_pair(OPERATION, string(1, str[i])));
            } else if (isdigit(str[i])) {
                tmp.push_back(str[i]);
                state = NUMBER;
            } else if (str[i] == '.') {
                state = END;
            } else if (str[i] == '(' || str[i] == ')') {
                lexems.push_back(make_pair(BRACKET, string(1, str[i])));
            }
            i++;
        } else if (state == NUMBER) {
            if (isspace(str[i])) {
                state = WAIT;
                lexems.push_back(make_pair(NUMBER, tmp));
                tmp.clear();
            } else if (isoperation(str[i])) {
                state = WAIT;
                lexems.push_back(make_pair(NUMBER, tmp));
                tmp.clear();
                lexems.push_back(make_pair(OPERATION, string(1, str[i])));
            } else if (str[i] == '.') {
                state = END;
                lexems.push_back(make_pair(NUMBER, tmp));
                tmp.clear();
            } else if (str[i] == '(' || str[i] == ')') {
                state = WAIT;
                lexems.push_back(make_pair(NUMBER, tmp));
                tmp.clear();
                lexems.push_back(make_pair(BRACKET, string(1, str[i])));
            } else if (isdigit(str[i])) {
                tmp.push_back(str[i]);
            }
            i++;
        }
    }

    for (it = lexems.begin(); it != lexems.end(); it++) {
        cout << it->second << endl;
    }

    return 0;
}
