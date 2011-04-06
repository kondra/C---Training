#include <iostream>
#include <cmath>

using namespace std;

template <class TypeA> class Functor
{
public:
    template<class TypeB> Functor<TypeB> fmap(TypeB func(TypeA));
};

template <class TypeA> class Maybe : public Functor<TypeA>
{
    TypeA just;
    bool nothing;
public:
    Maybe() { nothing = true; }
    Maybe(TypeA a) : just(a), nothing(false) { }

    void Show() const {
        if (nothing)
            cout << "Nothing" << endl;
        else
            cout << "Just " << just << endl;
    }

    template <class TypeB> Maybe<TypeB> fmap(TypeB func(TypeA))
    {
        if (nothing == true)
            return Maybe<TypeB>();
        else
            return Maybe<TypeB>(func(just));
    }
};

template <class TypeA> class List : public Functor<TypeA>
{
    TypeA elem;
    List<TypeA> *next, *last;

    void helper() const {
        cout << ", " << elem;
        if (next)
            next->helper();
    }
public:
    List() : next(0) {
        last = this;
    }
    List(TypeA elem) : elem(elem), next(0) {
        last = this;
    }

    void Show() const {
        cout << "[" << elem;
        if (next)
            next->helper();
        cout << "]" << endl;
    }

    List<TypeA>& operator+ (const List<TypeA>& l) {
        List<TypeA> *tmp = new List(l);
        last->next = tmp;
        last = tmp;
        return *this;
    }

    template <class TypeB> List<TypeB> fmap(TypeB func(TypeA))
    {
        List<TypeB> *tmp = new List<TypeB>(func(elem));
        if (next)
            return *tmp + next->fmap(func);
        return *tmp;
    }
};

int func(int a) {
    return a * a;
}

double func2(int a) {
    return sqrt(a);
}

int main()
{
    Maybe<int> m1;
    Maybe<int> m2(10);

    m1.Show();
    m2.Show();

    Maybe<int> fm1;
    Maybe<double> fm2;

    fm1 = m1.fmap(func);
    fm2 = m2.fmap(func2);

    fm1.Show();
    fm2.Show();

    List<int> a(0);
    a = a + 1 + 20 + 50;
    a = a + 2;
    a = a + 5;
    a.Show();

    List<double> b;
    b = a.fmap(func2);
    b.Show();

    return 0;
}
