#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Function
{
    const int num;
public:
    Function(int num) : num(num) {}
    virtual ~Function() {}

    virtual double func(double x) const = 0; 
    virtual double operator() (double x) const {
        return func(x);
    }

    const int& get_num() const {
        return num;
    }
};

class Metric
{
protected:
    const double y;
    const double eps;
public:
    Metric(double y, double eps) : y(y), eps(eps) {}
    virtual ~Metric() {}

    virtual bool compare(const Function *f1, const Function *f2) const = 0;
};

//monomorphic wrapper; stl passes functors by value
class Comparator {
    Metric *metric;
public:
    Comparator(Metric *metric) : metric(metric) {}

    bool operator() (const Function *f1, const Function *f2) const {
        return metric->compare(f1, f2);
    }
};

///////////////////////////////////////////////////////////////////////////////

class Metric1 : public Metric {
public:
    Metric1(double y, double eps) : Metric(y, eps) {}

    bool compare(const Function *f1, const Function *f2) const {
        double x1 = (*f1)(y);
        double x2 = (*f2)(y);
        if (x1 < x2)
            return true;
        if (fabs(x1 - x2) < eps && f1->get_num() < f2->get_num())
            return true;
        return false;
    }
};

class Metric2 : public Metric {
public:
    Metric2(double y, double eps) : Metric(y, eps) {}

    bool compare(const Function *f1, const Function *f2) const {
        double x1 = (*f1)(y);
        double x2 = (*f2)(y);
        if (fabs(x1) < fabs(x2))
            return true;
        if (fabs(x1 - x2) < eps && f1->get_num() > f2->get_num())
            return true;
        return false;
    }
};

class Sin : public Function {
public:
    Sin() : Function(1) {}

    double func(double x) const {
        return sin(x);
    }
};

class Cos : public Function {
public:
    Cos() : Function(2) {}

    double func(double x) const {
        return cos(x);
    }
};

class Square : public Function {
public:
    Square() : Function(3) {}

    double func(double x) const {
        return x * x;
    }
};

class Fabs : public Function {
public:
    Fabs() : Function(4) {}

    double func(double x) const {
        return fabs(x);
    }
};

class Exp : public Function {
public:
    Exp() : Function(5) {}

    double func(double x) const {
        return exp(x);
    }
};

class Sqrt : public Function {
public:
    Sqrt() : Function(6) {}

    double func(double x) const {
        return sqrt(42 + x * x);
    }
};

class Cube : public Function {
public:
    Cube() : Function(7) {}

    double func(double x) const {
        return x * x * x;
    }
};

class Cos2 : public Function {
public:
    Cos2() : Function(8) {}

    double func(double x) const {
        return cos(x + M_PI / 3);
    }
};

class Sin2 : public Function {
public:
    Sin2() : Function(9) {}

    double func(double x) const {
        return sin(x - M_PI / 42);
    }
};

class Log : public Function {
public:
    Log() : Function(10) {}

    double func(double x) const {
        return log(2 + x * x);
    }
};

int main()
{
    const double eps = 1e-8;

    double z, y;
    int k;

    Metric *metric;

    cin >> k >> y >> z;

    if (k == 1)
        metric = new Metric1(y, eps);
    else if (k == 2)
        metric = new Metric2(y, eps);

    Comparator comp(metric);

    vector<Function*> arr;

    arr.push_back(new Sin());
    arr.push_back(new Cos());
    arr.push_back(new Square());
    arr.push_back(new Fabs());
    arr.push_back(new Exp());
    arr.push_back(new Sqrt());
    arr.push_back(new Cube());
    arr.push_back(new Cos2());
    arr.push_back(new Sin2());
    arr.push_back(new Log());

    sort(arr.begin(), arr.end(), comp);

    for (int i = arr.size() - 1; i >= 0; i--) {
        z = arr[i]->func(z);
    }

    cout << setprecision(10) << z << endl;

    return 0;
}
