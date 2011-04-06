#include <iostream>

using namespace std;

template<class T>
class Compl {
    T r;
    T i;
public:
    Compl(T r=T(), T i=T()) : r(r), i(i) {
    }

    Compl<T> operator* (const Compl<T>& c) {
        T tr = r * c.r - i * c.i;
        T ti = r * c.i + i * c.r;
        return Compl<T>(tr, ti);
    }

    template<class T1> friend Compl<T1> operator*(const Compl<T1>& c1, const Compl<T1>& c2);
    template<class T1> friend ostream& operator<<(ostream& os, const Compl<T1>& c);
};

/*
template<class T>
Compl<T> operator*(const Compl<T>& c1, const Compl<T>& c2) {
    T tr = c1.r * c2.r - c1.i * c2.i;
    T ti = c1.r * c2.i + c1.i * c2.r;
    return Compl<T>(tr, ti);
}
*/

template<class T>
ostream& operator<< (ostream& os, const Compl<T>& c) {
    os << c.r << "+" << c.i << "i" << endl;
    return os;
}

int main()
{
    Compl<int> c1(0, 1), c2(0, 1), c3(0, 0);

    cout << c1;
    cout << c2;
    cout << c3;
    cout << c1 * c2 * c3;

    return 0;
}
