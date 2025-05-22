#include <chrono>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
using namespace std::chrono;

std::set<pair<int, int>> myset;
double T;

struct Type {
    int id;
    int value;
    bool operator<(const Type& that) const {  // const is  required
        if (value != that.value)
            return value < that.value;
        return id > that.id;
        // this < that
    }
    bool operator>(const Type& that) const {  // const is  required
        if (value != that.value)
            return value > that.value;
        return id < that.id;
        // this < that
    }
    bool operator==(const Type that) {  // const is  required
        if (value != that.value)
            return value < that.value;
        return id > that.id;
        // this < that
    }
} t1, t2;  // t1 < t2; t1 != t2

int minInt = -0x7FFFFFFF;

struct compare {
    bool
    operator()(const Type& x, const Type& y) const {
        return x.value < y.value;
    }
};

struct Less {
    bool
    operator()(const Type& __x, const Type& __y) const {
        if (__x.value != __y.value)
            return __x.value < __y.value;
        return __x.id > __y.id;
    }
};

set<Type> tree;
// set<Type, greater<Type>> tree2;
set<int, less<int>> t;

struct comparePointer {
    bool
    operator()(const Type* x, const Type* y) const {
        return x->value < x->value;
    }
};

set<Type*, comparePointer> setp;

int main() {
    Type x = {0, 1};
    Type y = {0, 2};
    Type z = {0, 3};
    Type w = {0, 4};
    auto ittt = tree.insert(x).first;
    tree.insert(y);
    tree.insert(z);
    tree.insert(w);
    tree.insert({0, 5});

    set<Type> test;

    tree.find({0,0});

    auto it = tree.find(/* your Type*/); // iterator
    if (it != tree.end()) { // like null check. if equal, it not exist in your set
        // Do your stuff
    }

    cout << it->value << endl;

    auto it2 = tree.end();
    --it2;
    cout << it2->value << endl;

    for (auto it : tree) {
        cout << it.value << " ";
    }
    cout << endl;
    tree.erase(w);




    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << it->value << " ";
        (*it).value;
        
    }

    for (auto it = test.begin(); it != test.end(); it++) {
        t1 = *it;
    }

    auto st = high_resolution_clock::now();

    // std::set<int>::iterator itlow, itup;

    // for (int i = 1; i < 10; i+=2)
    //     myset.insert(make_pair(i,-1));  // 10 20 30 40 50 60 70 80 90

    myset.insert(make_pair(0, 0));
    auto itlow = myset.upper_bound(make_pair(1, minInt));
    cout << itlow->first << " " << itlow->second << endl;
    if (itlow->first == 1) {
        myset.erase(itlow);
        myset.insert(make_pair(0, 10));
    } else
        myset.insert(make_pair(0, 99));

    itlow = myset.lower_bound(make_pair(0, 0));
    cout << itlow->first << " " << itlow->second << endl;

    // for (int i = 1; i < 1000000; i++)

    itlow = myset.lower_bound(20);  //       ^
    itup = myset.upper_bound(35);   //                   ^
    //myset.clear();
    myset = *new set<int>;
    auto en = high_resolution_clock::now();
     = duration_cast<nanoseconds>(en - st).count();
    cout << T/1e9 << endl;
    cout << *itlow << endl;
    cout << *itup << endl;
    cout << myset.size();
    //myset.erase(itlow, itup);  // 10 20 70 80 90

    st = high_resolution_clock::now();

    for (int i = 1; i < 1000000; i++)
        myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

    itlow = myset.lower_bound(20);  //       
    itup = myset.upper_bound(35);   //                   ^
    // myset.clear();
    myset.clear();
    /*auto en = high_resolution_clock::now();
    T = duration_cast<nanoseconds>(en - st).count();
    cout << T / 1e9 << endl;*/
    std::cout << "myset contains:";
    for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}