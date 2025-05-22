#include <iostream>

using namespace std;
#define MAX_ARR 0xFFFFF

struct ID {
    int value;
    //for heap
    int heapIndex;
} INDEX[MAX_ARR];
int idCount = 0;

typedef bool (*comparator)(int, int);

bool minHeap(int a, int b) {
    return INDEX[a].value > INDEX[b].value;
}
bool maxHeap(int a, int b) {
    return INDEX[a].value < INDEX[b].value;
}
int step = 0;

struct Heap {
    int id[MAX_ARR];
    int size;
    comparator comp;
    Heap(comparator cmp) {
        comp = cmp;
        size = 0;
    }
    void Swap(int a, int b) {
        int t = id[a];
        id[a] = id[b];
        id[b] = t;
        INDEX[a].heapIndex = a;
        INDEX[b].heapIndex = b;
    }
    void insert(int data) {
        INDEX[idCount].value = data;
        INDEX[idCount].heapIndex = size;
        id[size] = idCount++;
        up(size++);
    }
    void up(int index) {
        int indx = index;
        int parent = (index - 1) / 2;
        if (index > 0)
            if (comp(id[parent], id[indx]))
                indx = parent;
        if (index != indx) {
            Swap(index, indx);
            up(indx);
        }
    }
    void down(int index) {
        int indx = index;
        int left = 2 * indx + 1;
        int right = 2 * index + 2;
        if (left < size)
            if (comp(id[indx], id[left]))
                indx = left;
        if (right < size)
            if (comp(id[indx], id[right]))
                indx = right;
        if (index != indx) {
            Swap(index, indx);
            down(indx);
        }
    }
    int pop() {
        if (size == 0)
            return -1;
        Swap(0, --size);
        down(0);
        return id[size];
    }
    void update(int index) {
        cout << "update " << index << endl;
        up(index);
        cout << "update " << index << endl;
        down(index);
    }
    void mDelete(int index) {
        Swap(index, --size);
        update(index);
    }
} mHeap(minHeap);

int main() {
    int n = 10;
    for (int i = 0; i < n; i++) {
        mHeap.insert(rand() % 100);
    }
    for (int i = 0; i < n; i++) {
        cout << i << " " << INDEX[i].value << " " << INDEX[i].heapIndex << endl;
    }
    cout << endl;
    // update test
    INDEX[3].value = 999;
    mHeap.update(INDEX[3].heapIndex);
    //mHeap.mDelete(INDEX[6].heapIndex);
    for (int i = 0; i < n; i++) {
        cout << i << " " << INDEX[i].value << " " << INDEX[i].heapIndex << endl;
    }
    cout << endl;
    int s = mHeap.size;
    for (int i = 0; i < s; i++) {
        int id = mHeap.pop();
        cout << id << " " << INDEX[id].value << endl;
    }
    cout << step;
    return 0;
}
