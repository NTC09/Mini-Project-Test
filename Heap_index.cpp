#include <iostream>

using namespace std;

#define MAX_ARR 10

int step = 0;

struct Array {
    int data;
    int indexInHeap;
} arr[MAX_ARR];

typedef bool (*comparator)(int&, int&);
bool minHeap(int& a, int& b) {
    return arr[a].data > arr[b].data;
}
bool maxHeap(int& a, int& b) {
    return arr[a].data < arr[b].data;
}

struct Heap {
    int indexOfArr[MAX_ARR];
    int size;
    comparator comp;
    Heap(comparator cmp) {
        comp = cmp;
        size = 0;
    }
    int& operator[](int index) {
        return this->indexOfArr[index];
    }
    void insert(int data) {
        arr[size].data = data;
        arr[size].indexInHeap = size;
        (*this)[size] = size;
        up(size++);
    }
    void up(int index) {
        int indx = index;
        if (indx >= 0)
            if (comp((*this)[(indx - 1) / 2], (*this)[indx]))
                indx = (index - 1) / 2;
        if (index != indx) {
            Swap(index, indx);
            up(indx);
        }
    }
    void down(int index) {
        int indx = index;
        if (2 * indx + 1 < size)
            if (comp((*this)[indx], (*this)[2 * index + 1]))
                indx = 2 * index + 1;
        if (2 * index + 2 < size)
            if (comp((*this)[indx], (*this)[2 * index + 2]))
                indx = 2 * index + 2;
        if (index != indx) {
            Swap(index, indx);
            down(indx);
        }
    }
    void down(int root, int index) {
        step++;
        int indx = index;
        if (2 * index + 1 < root)
            if (comp((*this)[2 * index + 1], (*this)[indx]))
                indx = 2 * index + 1;
        if (2 * index + 2 < root)
            if (comp((*this)[2 * index + 2], (*this)[indx]))
                indx = 2 * index + 2;
        if (index != indx) {
            Swap(index, indx);
            down(root, indx);
        }
    }
    int pop() {
        if (size == 0)
            return 0;
        Swap(0, --size);
        down(0);
        cout << (*this)[size] << " ";
        return arr[(*this)[size]].data;
    }
    void update(int index) {
        up(index);
        down(index);
    }
    void sort() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            down(size, i);
        }
        for (int i = size - 1; i >= 0; i--) {
            Swap(0, i);
            down(i, 0);
        }
    }
    void Swap(int i, int j) {
        swap(arr[indexOfArr[i]].indexInHeap, arr[indexOfArr[j]].indexInHeap);
        swap((*this)[i], (*this)[j]);
    }
} mHeap(maxHeap);

int main() {
    int t, n = MAX_ARR;
    for (int i = 0; i < n; i++) {
        t = (rand() % 100);
        mHeap.insert(t);
    }
    arr[5].data = 999;
    mHeap.update(arr[5].indexInHeap);
    //mHeap.sort();
    for (int i = 0; i < n; i++) {
        cout << mHeap.pop() << " \t"  << i<< " " <<arr[i].data << endl;
    }
    //cout << step;
    return 0;
}
