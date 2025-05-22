#pragma GCC optimize("O3,unroll-loops")
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;
using namespace std::chrono;

#define MAX_ARR (0xFFFFF)

class SubClass {
   private:
    int value;

   public:
    void setValue(int value) { this->value = value; }
    int getValue() { return this->value; }
    bool operator<(SubClass& mMyClass) const {
        return this->value < mMyClass.value;
    }
} MyData[MAX_ARR];

template <typename SubClass>
class Heap {
   private:
    static const int ARR_SIZE = 100007;
    class HeapId {
       public:
        int Heapindex;
        SubClass* subClass;
        int next;
        bool operator<(HeapId& mMyClass) const {
            return *(this->subClass) < *(mMyClass.subClass);
        }
    } elements[ARR_SIZE];
    int Heapindex[ARR_SIZE];
    int mapHeapId[ARR_SIZE];
    int size;
    // int capacity;
    bool isMaxHeap;

   public:
    Heap() {
        size = 0;
    }
    void initForMaxHeap() {
        size = 0;
        isMaxHeap = true;
        for (int i = 0; i < ARR_SIZE; i++) {
            mapHeapId[i] = -1;
        }
    }
    void initForMinHeap() {
        size = 0;
        isMaxHeap = false;
        for (int i = 0; i < ARR_SIZE; i++) {
            mapHeapId[i] = -1;
        }
    }
    int getHeapId(SubClass* mSubClass) {
        intptr_t address = reinterpret_cast<intptr_t>(mSubClass);
        int temp = mapHeapId[address % ARR_SIZE];
        while (temp != -1 && elements[temp].subClass != mSubClass)
            temp = elements[temp].next;
        return temp;
    }
    void deleteMap(int index) {
        intptr_t address = reinterpret_cast<intptr_t>(elements[index].subClass);
        int hash = address % ARR_SIZE;
        int temp = mapHeapId[hash];
        if (temp == index) {  // root
            mapHeapId[hash] = elements[temp].next;
            return;
        }
        while (temp != -1 && elements[temp].next != index)
            temp = elements[temp].next;
        if (temp != -1)
            elements[temp].next = elements[index].next;
    }
    void insert(SubClass* mSubClass) {
        elements[size].subClass = mSubClass;
        elements[size].Heapindex = size;
        intptr_t address = reinterpret_cast<intptr_t>(mSubClass);
        int hash = address % ARR_SIZE;
        elements[size].next = mapHeapId[hash];
        mapHeapId[hash] = size;
        Heapindex[size] = size;
        heapifyUp(size++);
    }
    void heapifyUp(int index) {
        int nextId = index,
            parent = (index - 1) / 2;
        if (parent >= 0) {
            if ((elements[Heapindex[parent]] < elements[Heapindex[nextId]]) == isMaxHeap)
                nextId = parent;
        }
        if (nextId != index) {
            Swap(nextId, index);
            heapifyUp(nextId);
        }
    }
    void heapifyDown(int index) {
        int nextId = index,
            left = 2 * index + 1,
            right = 2 * index + 2;
        if (left < size) {
            if ((elements[Heapindex[nextId]] < elements[Heapindex[left]]) == isMaxHeap)
                nextId = left;
        }
        if (right < size) {
            if ((elements[Heapindex[nextId]] < elements[Heapindex[right]]) == isMaxHeap)
                nextId = right;
        }
        if (nextId != index) {
            Swap(nextId, index);
            heapifyDown(nextId);
        }
    }
    void update(SubClass* mSubClass) {
        int index = getHeapId(mSubClass);
        if (index == -1) {
            cout << "Not found!\n";
            return;
        }
        cout << "updating " << mSubClass->getValue() << endl;
        // cout << index << " " << Heapindex[index] << " " << elements[Heapindex[index]].subClass->getValue() << endl;
        heapifyUp(index);
        heapifyDown(index);
        cout << "New location " << getHeapId(mSubClass) << endl;
    }
    void Swap(int id1, int id2) {
        int t = Heapindex[id1];
        Heapindex[id1] = Heapindex[id2];
        Heapindex[id2] = t;
        elements[Heapindex[id1]].Heapindex = id1;
        elements[Heapindex[id2]].Heapindex = id2;
    }
    void erase(SubClass* mSubClass) {
        int index = getHeapId(mSubClass);
        if (index == -1) {
            cout << "Not found!\n";
            return;
        }
        Swap(index, --size);
        heapifyDown(index);
        heapifyUp(index);
        deleteMap(index);
    }
    SubClass* pop() {
        if (size == 0)
            return NULL;
        Swap(0, --size);
        heapifyDown(0);
        cout << Heapindex[size] << " \t";
        return elements[Heapindex[size]].subClass;
    }
    int getSize() { return size; }
};
Heap<SubClass> mheap, heap2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    auto st = high_resolution_clock::now();
    cout << "Started!" << endl;
    int n = 10;
    mheap.initForMaxHeap();
    heap2.initForMinHeap();
    for (int i = 0; i < n; i++) {
        MyData[i].setValue(rand()%1000);
        mheap.insert(&MyData[i]);
    }
    MyData[3].setValue(999999);
    mheap.update(&MyData[3]);
    MyData[4].setValue(-999);
    mheap.update(&MyData[4]);
    cout << "Heap Started!" << endl;
    //mheap.erase(&MyData[2]);
    //mheap.update(&MyData[2]);
    //mheap.erase(&MyData[2]);
    int size = mheap.getSize();
    for (int i = 0; i < size; i++) {
        SubClass* t = mheap.pop();
        if (t == NULL)
            continue;
        cout << t->getValue() << " \t" << i << " \t" << MyData[i].getValue() << endl;
    }
    cout << "Heap Started!" << endl;
    auto en = high_resolution_clock::now();
    double t = duration_cast<nanoseconds>(en - st).count();
    cout << t / 1e9;
    return 0;
}