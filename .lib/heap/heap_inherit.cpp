#include <iostream>
using namespace std;

class HeapIndex {
   public:
    int heapid;
};

class HIndex : public HeapIndex {
   public:
    int value;
    bool operator<(HIndex& st) const {
        return this->value < st.value;
    }
    class H2 {

    };
} index[100];

template <typename HIndex>
class Heap {
   private:
    HIndex* List[1001];
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
        List[a]->heapid = a;
        List[b]->heapid = b;
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
        if (size == 1001) {
            if (*newValue < *List[this->size - 1])
                erase(this->size - 1);
            else
                return;
        }
        this->List[this->size] = newValue;
        newValue->heapid = this->size;
        heapifyUp(this->size++);
    }
    
    void erase(HIndex* type) {
        erase(type->heapid);
    }
    void update(HIndex* type) {
        update(type->heapid);
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
