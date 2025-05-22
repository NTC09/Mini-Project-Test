#include <iostream>
#include <set>

using namespace std;

template <typename arg1, typename arg2, typename result>
struct compareFunction {
    typedef arg1 first_argument_type;
    typedef arg2 second_argument_type;
    typedef result result_type;
};
/*
template <typename Type>
class bigger : public compareFunction <Type, Type, bool>{
    public:
    //_GLIBCXX14_CONSTEXPR
    bool operator()(const typename Type& a, const typename Type& b) const {
        return a > b;
    }
};*/

template <typename Type>
class smaller{
    public:
    bool operator()(const Type& t1, const Type& t2) const {
        return t1 < t2;
    }
};

less<int> ll;

template <typename Type, typename compare = smaller<Type>>
class Tree {
    public:
     int res;
     compare comp;
     int test() {
        int a = 1;
        int b = 2;
        return comp(a, b);
     }
};
Tree<int> tree;

set<int> ss;

int a[1000000];
int main() {
    cout << tree.test();
    return 0;
}