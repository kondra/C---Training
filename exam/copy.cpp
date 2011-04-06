#include <iostream>

class A 
{
public:
    A(){std::cout << "A()" << std::endl;}
    A(A& a){std::cout << "A(A& a)" << std::endl;}
};

class AA : public A
{
public:
    AA(){std::cout << "AA()" << std::endl;}
//    AA(AA& a){std::cout << "AA(AA& a)" << std::endl;}
};

int main()
{
    AA aa;
    AA a(aa);
    return 0;
}
