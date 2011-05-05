#include <iostream>
#include <iterator>

using namespace std;

template<class BidirectionalIterator, class Predicate>
unsigned int myfilter(BidirectionalIterator begin, BidirectionalIterator end, const Predicate& pred, 
        typename iterator_traits<BidirectionalIterator>::value_type val = typename iterator_traits<BidirectionalIterator>::value_type())
{
    BidirectionalIterator it;
    unsigned int cnt = 0;

    if (begin == end)
        return 0;

    for (it = begin; it != end; it++) {
        if (pred(*it)) {
            *it = val;
            cnt++;
        }
    }

    return cnt;
}

/*
struct Pred {
    bool operator() (int v) const {
        return v > 10;
    }
};

int main()
{
    list<int> v;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<list<int> >(v, v.begin()));

    unsigned int cnt = myfilter(v.begin(), v.end(), Pred(), 5);
//    myfilter(v.begin(), v.end(), Pred());

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

    cout << "\nchanged:" << cnt<< endl;

    return 0;
}
*/
