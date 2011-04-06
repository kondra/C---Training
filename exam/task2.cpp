#include <iostream>

using namespace std;

int x = 0;  

int f() { 
    return x = 1;
}  

class A { 
    int x;  
public:
    A(int n = 2) { 
        x = n;  
        cout << "A::A(" << n << ")" << endl;
    }
    A(const A&) {
        cout << "A::A(A&)" << endl;
    }
    ~A() {
        cout << "A::~A()" << endl;
    }
    int f() { 
        return x = 3;
    }  
    int f(int a, int b) {
        return x = a % b;
    }
};  

class B: public A {
    int x;  
public:
    B() {
        cout << "B::B()" << endl;
    }
    ~B() {
        cout << "B::~B()" << endl;
    }
    int f (int a) { 
        return x = a;     
    }  
    int f (int a, int b) { 
        return x = a + b; 
    }
    int g(A *a, B *b);
};

int  B::g (A *pa, B *pb)  
{
    x =      A::f();  
    x =      f(5);  
    x =      f(6, 6);  
    x = B::     f(5);  
    return -1;
}  
/*
int main ()  
{ 
    B a;
    x = a.     A::f();  
    x = a.     f(7);  
    return a.     g(&a, &a);
}  
*/

int main()
{
    A a;
    class C {
        B b;
        A a;
    public:
        C() : b(), a(b) {
            cout << "C::C()" << endl;
        }
        ~C() {
            cout << "C::~C()" << endl;
        }
    };
    C c;
    return 0;
}
