#include <iostream>

using namespace std;
#define MAX_ARR 0xFFFFF

struct ID {
    int value;
    //for heap
    int heapIndex;
} INDEX[MAX_ARR];

//typedef bool (*comparator)(int&, int&);

bool minHeap(int& a, int& b) {
    return INDEX[a].value > INDEX[b].value;
}
bool maxHeap(int& a, int& b) {
    return INDEX[a].value < INDEX[b].value;
}
int step = 0;

struct Heap {
    int id[MAX_ARR];
    int size;
    bool (*comp)(int&, int&);
    Heap(bool (*cmp)(int&, int&)) {
        comp = cmp;
        size = 0;
    }
    void Swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }

    int& operator[](int index) {
        return this->id[index];
    }
    void insert(int data) {
        (*this)[size] = data;
        up(size++);
    }
    void up(int index) {
        int indx = index;
        if ((indx - 1) / 2 >= 0)
            if (comp((*this)[(indx - 1) / 2], (*this)[indx]))
                indx = (index - 1) / 2;
        if (index != indx) {
            Swap((*this)[index], (*this)[indx]);
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
            Swap((*this)[index], (*this)[indx]);
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
            Swap((*this)[index], (*this)[indx]);
            Swap(INDEX[index], INDEX[indx]);
            down(root, indx);
        }
    }
    int pop() {
        if (size == 0)
            return 0;
        Swap((*this)[0], (*this)[--size]);
        Swap(INDEX[0], INDEX[size]);
        down(0);
        return (*this)[size];
    }
    void update(int index, int newid) {
        (*this)[index] = newid;
        up(index);
        down(index);
    }
    void sort() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            down(size, i);
        }
        for (int i = size - 1; i >= 0; i--) {
            Swap((*this)[0], (*this)[i]);
            Swap(INDEX[0], INDEX[i]);
            down(i, 0);
        }
    }
} mHeap(maxHeap);

int main() {
    int n = 1000000;
    for (int i = 0; i < n; i++) {
        mHeap[i] = (rand() % 100);
        // INDEX[i] = i;
    }
    mHeap.size = n;
    mHeap.sort();
    /*for (int i = 0; i < n; i++) {
        cout << mHeap.pop() << " " << INDEX[i] << endl;
    }*/
    cout << step;
    return 0;
}
