#include <iostream>
using namespace std;

struct HeapIndex {
    int heapId;
};

struct HIndex : HeapIndex {
    int value;
    bool operator<(HIndex& st) const {
        return this->value < st.value;
    }
} index[100];

template <typename HIndex>
class Heap {
   private:
    HIndex* List[1000];
    bool isMaxHeap;
    unsigned int size;
    void heapifyUp(int index) {
        register int indx = index,
                     parent = (indx - 1) / 2;
        if (parent >= 0) {
            if (comp(parent, indx))
                indx = parent;
        }
        if (indx != index) {
            Swap(indx, index);
            heapifyUp(indx);
        }
    }
    void heapifyDown(int index) {
        register int indx = index,
                     left = 2 * indx + 1,
                     right = 2 * indx + 2;
        if (left < size)
            if (comp(indx, left))
                indx = left;
        if (right < size)
            if (comp(indx, right))
                indx = right;
        if (indx != index) {
            Swap(indx, index);
            heapifyDown(indx);
        }
    }
    void erase(int index) {
        Swap(index, --this->size);
        heapifyDown(index);
        heapifyUp(index);
    }
    void update(int index) {
        heapifyUp(index);
        heapifyDown(index);
    }
    void Swap(int a, int b) {
        register HIndex* t = List[a];
        List[a] = List[b];
        List[b] = t;
        List[a]->heapId = a;
        List[b]->heapId = b;
    }
    bool comp(int id1, int id2) {
        return (*List[id1] < *List[id2]) == isMaxHeap;
    }
   public:
    Heap() {
        this->init(true);
    }
    void init(bool heapType) {
        this->size = 0;
        isMaxHeap = heapType;
    }
    void init() {
        this->size = 0;
        isMaxHeap = true;
    }
    void insert(HIndex* newValue) {
        if (size == 1000)
            return;
        this->List[this->size] = newValue;
        newValue->heapId = this->size;
        heapifyUp(this->size++);
    }
    
    void erase(HIndex* type) {
        erase(type->heapId);
    }
    void update(HIndex* type) {
        update(type->heapId);
    }
    HIndex* pop() {
        Swap(0, --this->size);
        heapifyDown(0);
        return this->List[this->size];
    }
    HIndex* top() {
        if (size == 0)
            return 0;
        return this->List[0];
    }
};

Heap<HIndex> heap;

int main() {
    heap.init(false);
    for (int i = 0; i < 10; i++) {
        index[i].value = rand();
        heap.insert(&index[i]);
    }
    for (int i = 0; i < 10; i++) {
        HIndex* t = heap.pop();
        cout << t->value << " ";
    }
    return 0;
}
