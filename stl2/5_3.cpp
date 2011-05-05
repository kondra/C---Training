#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//is it really bad to include my operators to namespace std?
//namespaces are defective by design
//namespace std {
//ostream& operator<<(ostream& os, const pair<int, string>& p) {
//    os << p.first << ' ' << p.second;
//    return os;
//}
//the same shit
//bool operator<(const pair<int, string>& p1, const pair<int, string>& p2) {
//    return p1.first < p2.first;
//}
//}

struct my_out {
    void operator()(const pair<int, string>& p) const {
        cout << p.first << ' ' << p.second << endl;
    }
};

struct my_less {
    bool operator()(const pair<int, string>& p1, const pair<int, string>& p2) const {
        return p1.first < p2.first;
    }
};

int main()
{
    vector<pair<int, string> > pupils;
    string str;
    int n;

    while (true) {
        cin >> n;
        cin >> str;
        if (cin.eof())
            break;
        pupils.push_back(pair<int, string>(n, str));
    }

    stable_sort(pupils.begin(), pupils.end(), my_less());

//    NO WAY
//    ostream_iterator<pair<int, string> > out_it(cout, "\n");
//    copy(pupils.begin(), pupils.end(), out_it);

    for_each(pupils.begin(), pupils.end(), my_out());

    return 0;
}
