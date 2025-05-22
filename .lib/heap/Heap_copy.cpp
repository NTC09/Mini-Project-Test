#include <iostream>

using namespace std;

#define MAX_ARR 0xFFFFF

int INDEX[MAX_ARR];
int step = 0;

struct Heap { // value[0] is max
    int value[MAX_ARR];
    int size;
    Heap() {
        size = 0;
    }
    void insert(int data) {
        value[size] = data;
        up(size++);
    }
    void Swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }
    void up(int index) {
        int indx = index;
        if ((indx - 1) / 2 >= 0)
            if (value[(indx - 1) / 2] > value[indx])
                indx = (index - 1) / 2;
        if (index != indx) {
            Swap(value[index], value[indx]);
            up(indx);
        }
    }
    void down(int index) {
        int indx = index;
        int left = 2 * indx + 1;
        int right = 2 * index + 2;
        if (left< size)
            if (value[indx] > value[left])
                indx = left;
        if ( right< size)
            if (value[indx] > value[right])
                indx = right;
        if (index != indx) {
            Swap(value[index], value[indx]);
            down(indx);
        }
    }
    void down(int root, int index) {
        step++;
        int indx = index;
        if (2 * index + 1 < root)
            if (value[2 * index + 1], value[indx])
                indx = 2 * index + 1;
        if (2 * index + 2 < root)
            if (value[2 * index + 2], value[indx])
                indx = 2 * index + 2;
        if (index != indx) {
            Swap(value[index], value[indx]);
            down(root, indx);
        }
    }
    int pop() {
        if (size == 0)
            return 0;
        Swap(value[0], value[--size]);
        down(0);
        return value[size];
    }
    void update(int index, int newValue) {
        value[index] = newValue;
        up(index);
        down(index);
    }

    void sort() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            down(size, i);
        }
        for (int i = size - 1; i >= 0; i--) {
            Swap(value[0], value[i]);
            Swap(INDEX[0], INDEX[i]);
            down(i, 0);
        }
    }
} mHeap;

int main() {
    int n = 15;
    for (int i = 0; i < n; i++) {
        if (i == 3)
            mHeap.insert(9999);
        mHeap.insert(rand() % 100);
        // INDEX[i] = i;
    }
    //mHeap.size = n;
    //mHeap.sort();
    for (int i = 0; i < n; i++) {
        cout << mHeap.pop() << endl;
    }
    //cout << step;
    return 0;
}
