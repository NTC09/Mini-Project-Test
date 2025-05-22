#include <algorithm> // this is the library used in this guide
#include <iostream>

using namespace std;

#define MAXS 10 // this is capacity. Calculate it carefully
#define R register

struct T {
    int v1;
    int v2;
};

T mheap[MAXS]; // this is the heap array
int hsize = 0; // size of heap, simply assign 0 to it to reset the heap

struct comp { // the compare struct for the heap. you can replace this by implementing operator <.
    bool operator()(const T& a, const T& b) {
        return a.v1 == b.v1 ? a.v2 < b.v2 : a.v1 > b.v1;
    }
};
comp cm; // you must create a variable to pass it to the function

int main() {
    for (R int i = 0; i < MAXS; ++i) {
        mheap[hsize].v1 = rand() % 97;
        mheap[hsize].v2 = rand() % 5; 	// assign new element to heap
		++hsize;				  		// remember to increase the heap size before call push_heap
        cout << mheap[i].v1 << " " << mheap[i].v2 << endl ;
        push_heap(mheap, mheap + hsize, cm);
		// when push a new element to heap, simply assign it to last index of the heap
		// mheap is the start pointer of your heap
		// mheap + hsize is the current last pointer of your heap
    }
    cout << "=======" << endl;
    for (R int i = 0; i < MAXS; ++i) {
        cout << mheap[0].v1 << " " << mheap[0].v2 << endl; // the element in index 0 is top of the heap
        pop_heap(mheap, mheap + hsize, cm);
        --hsize;
		// when pop the heap, remember to reduce the size by one
    }
}