#define MIN_HEAP
template <typename __T>
class MinHeap {
#ifdef MIN_HEAP
#define R register
#define i_ int
#define v_ void
#define u_ unsigned
#define b_ bool
#define r_(e) return (e);
#define SIZE 1000
   private:
    __T* __3;u_ i_ __s;v_ __2(i_ _i) {R i_ __i=_i,__p=(__i-1)/2;if(__p>=0){if(
    __2(__p,__i))__i=__p;}if (__i!=_i){__1(__i,_i);__2(__i);}}v_ __1(i_ _i) {R
    i_ __i=_i,__l=2*__i+1,__r=2 * __i + 2;if(__l<__s)if(__2(__i,__l))__i=__l;if
    (__r<__s)if(__2(__i,__r))__i=__r;if (__i != _i){__1(__i,_i);__1(__i);}}v_
    __1(i_ __i,i_ _i) {R __T __t=__3[__i];__3[__i]=__3[_i];__3[_i]=__t;}b_ __2
    (i_ __1,i_ __2) {r_(__3[__2] < __3[__1])}
   public:
    MinHeap() {clear();__3=new __T[SIZE];}v_ clear() {__s=0;}v_ push(__T __t) {
    __3[__s]=__t;__2(__s++);}__T pop() {__1(0,--__s);__1(0);r_(__3[__s])}__T
    top() {if (__s == 0)r_(__T()) r_(__3[0])}b_ isEmpty(){r_(__s==0)}
#undef R
#undef i_
#undef v_
#undef u_
#undef b_
#undef r_
#undef SIZE
#endif
};


#include <iostream>
using namespace std;


int main() {
    // test
    MinHeap<int> m;

    for (int i_ = 0; i_ < 10; i_++)
        m.push(rand());

    while(!m.isEmpty())
        cout << m.pop() << " ";

    return 0;
}