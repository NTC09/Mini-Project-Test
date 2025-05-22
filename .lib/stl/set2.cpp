// #include <algorithm>
// #include <chrono>
// #include <iostream>
// #include <set>
// using namespace std;
// using namespace std::chrono;

// std::set<pair<int, int>> myset;
// double T;

// struct Type {
//     int id;
//     int value;
//     bool operator<(const Type& that) const {  // const is  required
//         if (value != that.value)
//             return value < that.value;
//         return id > that.id;
//         // this < that
//     }
//     bool operator>(const Type& that) const {  // const is  required
//         if (value != that.value)
//             return value > that.value;
//         return id < that.id;
//         // this < that
//     }
//     /*bool operator==(const Type that) {  // const is  required
//         if (value != that.value)
//             return value < that.value;
//         return id > that.id;
//         // this < that
//     }*/
// } t1, t2;  // t1 < t2; t1 != t2

// int minInt = -0x7FFFFFFF;

// struct compare {
//     bool
//     operator()(const Type& x, const Type& y) const {
//         return x.value < y.value;
//     }
// };

// struct Less {
//     bool
//     operator()(const Type& __x, const Type& __y) const {
//         if (__x.value != __y.value)
//             return __x.value < __y.value;
//         return __x.id > __y.id;
//     }
// };

// set<Type> tree;
// // set<Type, greater<Type>> tree2;
// set<int, less<int>> t;

// struct comparePointer {
//     bool
//     operator()(const Type* x, const Type* y) const {
//         return x->value < x->value;
//     }
// };

// set<Type*, comparePointer> setp;

// int main() {
//     Type x = {0, 1};
//     Type y = {0, 2};
//     Type z = {0, 3};
//     Type w = {0, 4};
//     tree.insert(x);
//     tree.insert(y);
//     tree.insert(z);
//     tree.insert(w);
//     tree.insert({0, 5});

//     Type h = {0, 4};

//     tree.erase(w);

//     auto it = tree.find(h);

//     if (it != tree.end())
//         cout << "Found";

//     return 0;
// }
#include <iostream>
#include<set>
using namespace std;

struct cmp{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const{
        if(a.first == b.first) return a.second<b.second;
        return a.first < b.first;
    }
};
set<pair<int, int>> s[3][2];

set<pair<int, int>, cmp> result;
// int search(int price, int s1, int s2){
//     for()
//     lower_bound(price, 0);
// }

int main(){
    result.insert(make_pair(31333, 123498773));
    result.insert(make_pair(31333, 88888888));
    auto it = result.rbegin();

    cout << it->second;
    return 0;
}