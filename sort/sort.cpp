#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Function
{
    static const double EPS = 1e-8;

    int num;
public:
    static double y;
    static int metric;

    class WrongFunction {};

    Function(int num) : num(num) {
        if (num > 10 || num < 1)
            throw WrongFunction();
    }

    double func(double x) const {
        switch (num) {
            case 1: return sin(x);
            case 2: return cos(x);
            case 3: return x * x;
            case 4: return fabs(x);
            case 5: return exp(x);
            case 6: return sqrt(42 + x * x);
            case 7: return x * x * x;
            case 8: return cos(x + M_PI / 3);
            case 9: return sin(x - M_PI / 42);
            case 10: return log(2 + x * x);
        }
        return 0;
    }

    bool operator< (const Function& f) const {
        if (metric == 1) {
            if (func(y) < f.func(y))
                return true;
            if (fabs(func(y) - f.func(y)) < EPS && num < f.num)
                return true;
        } else if (metric == 2) {
            if (fabs(func(y)) < fabs(f.func(y)) && num > f.num)
                return true;
            if (fabs(func(y) - f.func(y)) < EPS)
                return true;
        }
        return false;
    }
};

double Function::y;
int Function::metric;

int main()
{
    const int SIZE = 10;

    double z;

    cin >> Function::metric >> Function::y >> z;

    vector<Function> arr;

    for (int i = 1; i <= SIZE; i++) {
        arr.push_back(Function(i));
    }

    sort(arr.begin(), arr.end());

    for (int i = arr.size() - 1; i >= 0; i--) {
        z = arr[i].func(z);
    }

    cout << setprecision(10) << z << endl;

    return 0;
}
