#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

struct smartstr {
private:
    smartstr() {}
//    void* operator new(unsigned int);
//    void* operator new[](unsigned int);
};

int main()
{
//    smartstr ss;
    smartstr *ps = new smartstr;
    smartstr *s = new smartstr[10];
    return 0;
}
