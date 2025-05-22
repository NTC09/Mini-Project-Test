#include <time.h>
#include <chrono>
#include <iostream>

using namespace std;

void swap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

#define MAX_ARR 1000000

typedef bool (*comparator)(int&, int&);

bool _greater(int& a, int& b) {
    return a > b;
}

bool _less(int& a, int& b) {
    return a <= b;
}

struct Heap {
    int* value;
    int size;
    int left;
    int right;
    comparator comp;
    Heap(comparator cmp) {
        comp = cmp;
        size = 0;
        value = new int[MAX_ARR];
    }
    int& operator[](int index) {
        return this->value[index];
    }
    void insert(int data) {
        (*this)[size] = data;
        up(size++);
    }
    void up(int index) {
        int indx = index;
        if ((indx - 1) / 2 >= 0) {
            if (comp((*this)[(indx - 1) / 2], (*this)[indx]))
                indx = (indx - 1) / 2;
        }
        if (indx != index) {
            swap((*this)[indx], (*this)[index]);
            up(indx);
        }
    }
    void down(int index) {
        int indx = index;
        left = 2 * indx + 1;
        right = 2 * indx + 2;
        if (left < size) {
            if (comp((*this)[indx], (*this)[left]))
                indx = left;
        }
        if (right < size) {
            if (comp((*this)[indx], (*this)[right]))
                indx = right;
        }
        if (indx != index) {
            swap((*this)[indx], (*this)[index]);
            down(indx);
        }
    }

    int del(int index) {
        int result = (*this)[index];
        if (--size > 0) {
            (*this)[index] = (*this)[size];
            up(index);
            down(index);
        }
        return result;
    }
    void update(int index, int data) {
        (*this)[index] = data;
        up(index);
        down(index);
    }
};

int main() {
    auto str = chrono::high_resolution_clock::now();
    int t, n = 20;
    Heap heap(_greater);
    for (int i = 0; i < n; i++) {
        t = rand()%100;
        // cout << t << " ";
        heap.insert(t);
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << heap.del(0) << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    double cTime = chrono::duration_cast<chrono::microseconds>(end - str).count();
    cout << endl
         << cTime / 1e6;
    return 0;
}
