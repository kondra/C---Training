#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Frac
{
    int a, b;

    int gcd(int a, int b);
    void simplify();
    bool check(const Frac& f);
public:
    Frac(int a1=0, int b1=1) : a(a1) , b(b1) {
        if (b == 0)
            return;
        simplify();
    };

    Frac& operator= (const Frac& f);

    Frac& Add(const Frac& f);
    Frac& Substract(const Frac& f);
    Frac& Multiply(const Frac& f);
    Frac& Divide(const Frac& f);

    bool EqualTo(const Frac& f) const;
    int CompareTo(const Frac& f) const;

    bool IsInteger() const;

    string ToString() const;
};

int Frac::gcd (int a, int b)
{
    int c;
    while (b) {
        c = b;
        b = a % b;
        a = c;
    }
    return b;
}

void Frac::simplify()
{
    int c;
    while ((c = gcd(a, b)) != 1) {
        if (c == 0)
            break;
        a /= c;
        b /= c;
    }
}

bool Frac::check(const Frac& f)
{
    if (b == 0 || f.b) {
        b = 0;
        return true;
    }
    return false;
}

Frac& Frac::operator= (const Frac& f)
{
    if (this != &f) {
        a = f.a;
        b = f.b;
    }
    return *this;
}

Frac& Frac::Add(const Frac& f)
{
    check(f);
    a = a * f.b + b * f.a;
    b = b * f.b;
    simplify();
    return *this;
}

Frac& Frac::Substract(const Frac& f)
{
    check(f);
    a = a * f.b - b * f.a;
    b = b * f.b;
    simplify();
    return *this;
}

Frac& Frac::Multiply(const Frac& f)
{
    check(f);
    a *= f.a;
    b *= f.b;
    simplify();
    return *this;
}

Frac& Frac::Divide(const Frac& f)
{
    check(f);
    a *= f.b;
    b *= f.a;
    simplify();
    return *this;
}

bool Frac::EqualTo(const Frac& f) const
{
    if (f.a == a && f.b == b)
        return true;
    else
        return false;
}

int Frac::CompareTo(const Frac& f) const
{
    int c = a * f.b;
    int d = b * f.a;

    if (c > d)
        return 1;
    if (c < d)
        return -1;
    return 0;
}

bool Frac::IsInteger() const
{
    if (b == 1)
        return true;
    return false;
}

string Frac::ToString() const
{
    stringstream ss;
    if (b == 0) {
        if (a >= 0)
            return "+NAN";
        if (a < 0)
            return "-NAN";
    } else {
        ss << a << "/" << b;
    }
    return ss.str();
}

const Frac a(1,1);

int main()
{
    Frac q  = Frac(1, 3), w(1, 4);
    Frac s = 4;
    a.CompareTo(s);
    w = q;

    s.Add(q);

    s.Substract(q);
    s.Multiply(q);
    s.Divide(q);

    s.Add(q).Multiply(w);

    s.EqualTo(w);
    s.CompareTo(w);

    s.IsInteger();

    string str;
    Frac a(-1, 1), b(1, 1);
    str = b.ToString();
    cout << str << endl;
    str = a.ToString();
    cout << str << endl;

    a.Multiply(b);
    str = a.ToString();
    cout << str << endl;

    Frac arr[10];
    arr[0] = a;

    return 0;
}
