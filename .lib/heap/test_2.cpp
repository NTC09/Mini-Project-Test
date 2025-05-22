#include <algorithm> // this is the library used in this guide
#include <iostream>

using namespace std;

#define SIZE 20 // this is capacity. Calculate it carefully by numbers of calling push
#define R register

struct Type {
    int v1;
    int v2;
    // for update
    int stamp;
    Type* base;
};

struct comp { // the compare struct for the heap. you can replace this by implementing operator <.
    bool operator()(const Type& a, const Type& b) {
        return a.v1 == b.v1 ? a.v2 < b.v2 : a.v1 > b.v1;
    }
};

bool is_old_item(Type a) {
    return a.stamp != a.base->stamp; // use base pointer to point to global variable
}

struct Heap {
    int size;
    Type data[SIZE];
    comp cm; // you must create a variable to pass it to the function

    void clear() {
        size = 0;
    }
    void push(Type t) { // add new element to heap
        // remember, this just copy the element from global to heap
        // if you update the global variable, element inside heap will not update
        // even when you use pointer, the order will not auto update
        data[size++] = t; // remember to increase the heap size before call push_heap
        push_heap(data, data + size, cm);
        // when push a new element to heap, simply assign it to last index of the heap
		// data is the start pointer of your heap
		// data + size is the current last pointer of your heap
    }
    void pop() {
        if (size == 0) return;
        pop_heap(data, data + size, cm);
        --size;
        // when pop the heap, remember to reduce the size by one
    }
    Type top() {
        while (is_old_item(data[0])) pop(); // pop if element is not updated
        return data[0];// the element in index 0 is top of the heap
    }
};

Heap heap; // this is the heap array
Type type[10]; // must create global array so its pointer is visible

int main() {
    heap.clear();

    for (R int i = 0; i < 10; ++i) {
        type[i].v1 = rand() % 17;
        type[i].v2 = rand() % 17;
        type[i].stamp = 0;
        type[i].base = &type[i]; // point to self
        cout << type[i].v1 << " " << type[i].v2 << endl ;
        heap.push(type[i]);
    }
    cout << "=======" << endl;

    // update an element
    type[5].v1 = 10;
    type[5].v2 = 100;
    type[5].stamp++; // use stamp to check if element is old or new
    heap.push(type[5]);

    while (heap.size) {
        Type t = heap.top();
        heap.pop();
        cout << t.v1 << " " << t.v2 << endl; 
    }
}