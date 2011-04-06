#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Rational
{
    int a, b;

    int gcd(int a, int b);
    void simplify();
    bool check(const Rational& f);
public:
    Rational(int a=0, int b=1) : a(a) , b(b) {
        if (b == 0)
            return;
        simplify();
    };

    Rational& operator= (const Rational& f);

    Rational& Add(const Rational& f);
    Rational& Substract(const Rational& f);
    Rational& Multiply(const Rational& f);
    Rational& Divide(const Rational& f);

    bool EqualTo(const Rational& f) const;
    int CompareTo(const Rational& f) const;

    bool IsInteger() const;

    string ToString() const;
};

int Rational::gcd (int a, int b)
{
    int c;
    while (b) {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}

void Rational::simplify()
{
    int c;
    while ((c = gcd(a, b)) != 1) {
        if (c == 0)
            break;
        a /= c;
        b /= c;
    }
}

bool Rational::check(const Rational& f)
{
    if (b == 0 || f.b == 0) {
        b = 0;
        return true;
    }
    return false;
}

Rational& Rational::operator= (const Rational& f)
{
    if (this != &f) {
        a = f.a;
        b = f.b;
    }
    return *this;
}

Rational& Rational::Add(const Rational& f)
{
    check(f);
    a = a * f.b + b * f.a;
    b = b * f.b;
    simplify();
    return *this;
}

Rational& Rational::Substract(const Rational& f)
{
    check(f);
    a = a * f.b - b * f.a;
    b = b * f.b;
    simplify();
    return *this;
}

Rational& Rational::Multiply(const Rational& f)
{
    check(f);
    a *= f.a;
    b *= f.b;
    simplify();
    return *this;
}

Rational& Rational::Divide(const Rational& f)
{
    check(f);
    a *= f.b;
    b *= f.a;
    simplify();
    return *this;
}

bool Rational::EqualTo(const Rational& f) const
{
    if (f.a == a && f.b == b)
        return true;
    else
        return false;
}

int Rational::CompareTo(const Rational& f) const
{
    int c = a * f.b;
    int d = b * f.a;

    if (c > d)
        return 1;
    if (c < d)
        return -1;
    return 0;
}

bool Rational::IsInteger() const
{
    if (b == 1)
        return true;
    return false;
}

string Rational::ToString() const
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

const Rational a(1,1);

int main()
{
    Rational q  = Rational(1, 3), w(1, 4);
    Rational s = 4;
//    a.CompareTo(s);
    w = q;

    s.Add(q);
    cout << s.ToString() << endl;

    s.Substract(q);
    cout << s.ToString() << endl;

    s.Multiply(q);
    cout << s.ToString() << endl;

    s.Divide(q);
    cout << s.ToString() << endl;

    s.Add(q).Multiply(w);
    cout << s.ToString() << endl;

    s.EqualTo(w);
    s.CompareTo(w);

    s.IsInteger();

    cout << s.ToString() << endl;
//    cout << q.ToString() << endl;
//    cout << w.ToString() << endl;


    return 0;
}


