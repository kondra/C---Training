#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<string> hs;
    string str;
    char cmd;

    while (true) {
        cmd = cin.get();
        if (cmd == '#')
            break;
        cin.ignore();
        cin >> str;
        cin.ignore();

        if (cmd == '+')
            hs.insert(str);
        if (cmd == '-')
            hs.erase(str);
        if (cmd == '?') {
            if (hs.find(str) == hs.end())
                cout << "NO\n";
            else
                cout << "YES\n";
        }
    }

    return 0;
}
