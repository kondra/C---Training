#include <iostream>
#include <string>

using namespace std;

class Matrix;

class Wrapper
{
    const Matrix& a;
    int x, y;

    Wrapper(const Matrix& a, int x, int y) : a(a), x(x), y(y) {
        cout << "wrapper cons" << endl;
    }
public:
    ~Wrapper() {
        cout << "wrapper dest" << endl;
    }

    void operator= (const Matrix& b);
    void operator+= (const Matrix& b);
    Matrix& operator+ (const Matrix& b) const;

    friend class Matrix;
};

class Matrix
{
    int n, m;
    int **val;
public:
    class OutOfBound {};

    Matrix(int n, int m) : n(n), m(m) {
        cout << "matrix cons" << endl;
        int i, j;
        if (n <= 0 || m <= 0) 
            throw OutOfBound();
        val = new int*[n];
        for (i = 0; i < n; i++)
            val[i] = new int[m];
        for (i = 0; i < n; i++) 
            for (j = 0; j < m; j++)
                val[i][j] = 0;
    }

    Matrix(const Matrix& a) {
        cout << "matrix copy cons" << endl;
        int i, j;
        n = a.n;
        m = a.m;
        val = new int*[n];
        for (i = 0; i < n; i++)
            val[i] = new int[m];
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                val[i][j] = a.val[i][j];
            }
        }
    }

    ~Matrix() {
        cout << "matrix dest" << endl;
        for (int i = 0; i < n; i++)
            delete[] val[i];
        delete[] val;
    }

    Matrix& operator= (const Matrix& a);

    Wrapper& operator() (int i, int j) const {
        if (i < 0 || j < 0 || i >= n || j >= m)
            throw OutOfBound();
        Wrapper *tmp = new Wrapper(*this, i, j);
        return *tmp;
    }

    friend istream& operator>> (istream& in, Matrix& a);
    friend ostream& operator<< (ostream& out, const Matrix& a);

    friend class Wrapper;
};

Matrix& Matrix::operator= (const Matrix& a) {
    cout << "matrix =" << endl;
    int i, j;
    for (i = 0; i < n; i++)
        delete[] val[i];
    delete[] val;
    n = a.n;
    m = a.m;
    val = new int*[n];
    for (i = 0; i < n; i++) {
        val[i] = new int[m];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            val[i][j] = a.val[i][j];
        }
    }
    return *this;
}

void Wrapper::operator= (const Matrix& b) {
    int i, j;
    for (i = 0; i < b.n; i++) {
        for (j = 0; j < b.m; j++) {
            a.val[x + i][y + j] = b.val[i][j];
        }
    }
    this->~Wrapper();
}

void Wrapper::operator+= (const Matrix& b) {
    int i, j;
    for (i = 0; i < b.n; i++) {
        for (j = 0; j < b.m; j++) {
            a.val[x + i][y + j] += b.val[i][j];
        }
    }
    this->~Wrapper();
}

Matrix& Wrapper::operator+ (const Matrix& b) const {
    Matrix *tmp = new Matrix(b.n, b.m);
    *tmp = a;
    int i, j;
    for (i = 0; i < b.n; i++) {
        for (j = 0; j < b.m; j++) {
            tmp->val[x + i][y + j] += b.val[i][j];
        }
    }
    this->~Wrapper();
    return *tmp;
}

istream& operator>> (istream& in, Matrix& a) {
    int i, j;
    for (i = 0; i < a.n; i++) {
        for (j = 0; j < a.m; j++) {
            in >> a.val[i][j];
        }
    }
    return in;
}

ostream& operator<< (ostream& out, const Matrix& a) {
    int i, j;
    for (i = 0; i < a.n; i++) {
        for (j = 0; j < a.m; j++) {
            out << a.val[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

int main(void)
{
/*
    Matrix a(10, 12);
    Matrix c(4, 5);
    Matrix b1(3, 5);
    {
        Matrix b(3, 5);
        cin >> b;
        cout << b;
        b1 = b;
    }
    cout << b1;

    Matrix a2 = b1;
    cout << a2;
*/
    cout << "Testing:" << endl;
    const Matrix a(10, 12);
    Matrix b(3, 5);
    Matrix c(5, 5);

    cin >> b;

//    a(7, 7) = b;
//    c(1, 0) = b;

//    Matrix v(1, 1);
    Matrix v = a(0, 0) + b;
    v(4, 0) += b;
    v(7, 7) += b;
    v(7, 7) += b;

    cout << v;

    return 0;
}
