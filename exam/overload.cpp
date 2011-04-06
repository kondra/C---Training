#include <iostream>

using namespace std;

class Compl {
    double x, y;
public:
    Compl(double x = 0.0, double y = 0.0) : x(x), y(y) {
    }
    const double& Re() {
        return x;
    }
    const double& Im() {
        return y;
    }
    Compl& operator+=(const Compl& c) {
        x += c.x;
        y += c.y;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Compl& c);
};

inline Compl operator+(const Compl& c1, const Compl& c2) {
    Compl c(c1);
    c += c2;
    return c;
}

ostream& operator<<(ostream& out, const Compl& c) {
    out << c.x << " " << c.y << endl;
    return out;
}

int main()
{
    Compl c1(0, 1), c2(0, 1);
    cout << c1;
    cout << c2;

    Compl c3;
    c3 += c1;
    cout << c3;

    c1 = 1 + c2;
    cout << c1;

    Compl c4;
    c4 = c2 + 1;
    cout << c4;

    return 0;
}
