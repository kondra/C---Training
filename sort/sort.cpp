#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef bool (*Metric)(double, double, int, int, double);
typedef double (*Func)(double x); 

class Function
{
    int num;
    static int count;
    static double eps;

    Func func;
public:
    static double y;
    static Metric metric;

    Function(Func func) : func(func) {
        num = count++;
    }

    double calc_func(double x) const {
        return func(x);
    }

    bool operator< (const Function& f) const {
        return metric(func(y), f.func(y), num, f.num, eps);
    }
};

bool metric1(double x, double y, int n, int m, double eps) {
    if (x < y)
        return true;
    if (fabs(x - y) < eps && n < m)
        return true;
    return false;
}


bool metric2(double x, double y, int n, int m, double eps) {
    if (fabs(x) < fabs(y))
        return true;
    if (fabs(x - y) < eps && n > m)
        return true;
    return false;
}

double sqr(double x) {
    return x * x;
}

double mysqrt(double x) {
    return sqrt(42 + x * x);
}

double cube(double x) {
    return x * x * x;
}

double mycos(double x) {
    return cos(x + M_PI / 3);
}

double mysin(double x) {
    return sin(x - M_PI / 42);
}

double mylog(double x) {
    return log(2 + x * x);
}

double Function::y;
double Function::eps = 1e-8;
Metric Function::metric;
int Function::count = 1;

int main()
{
    int k;
    double z;

    cin >> k >> Function::y >> z;

    if (k == 1)
        Function::metric = metric1;
    else if (k == 2)
        Function::metric = metric2;

    vector<Function> arr;

    arr.push_back(Function(sin));
    arr.push_back(Function(cos));
    arr.push_back(Function(sqr));
    arr.push_back(Function(fabs));
    arr.push_back(Function(exp));
    arr.push_back(Function(mysqrt));
    arr.push_back(Function(cube));
    arr.push_back(Function(mycos));
    arr.push_back(Function(mysin));
    arr.push_back(Function(mylog));

    sort(arr.begin(), arr.end());

    for (int i = arr.size() - 1; i >= 0; i--) {
        z = arr[i].calc_func(z);
    }

    cout << setprecision(10) << z << endl;

    return 0;
}
