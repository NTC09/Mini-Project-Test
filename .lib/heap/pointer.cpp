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

// template <typename SubClass>
class Heap {
   private:
    static const int ARR_SIZE = 1000007;
    class HeapId {
       public:
        int Heapindex;
        SubClass* subClass;
        HeapId* next;
        bool operator<(HeapId& mMyClass) const {
            return *(this->subClass) < *(mMyClass.subClass);
        }
    } * elements;
    int Heapindex[ARR_SIZE];
    HeapId* mapHeapId[ARR_SIZE];
    int size;
    HeapId* deletedList;

    // int capacity;
    bool isMaxHeap;

   public:
    Heap() {
        size = 0;
    }
    int getSize() { return this->size; }
    void initForMaxHeap() {
        size = 0;
        isMaxHeap = true;
        deletedList = 0;
        for (int i = 0; i < ARR_SIZE; i++) {
            mapHeapId[i] = 0;
        }
    }
    void initForMinHeap() {
        size = 0;
        isMaxHeap = false;
        deletedList = 0;
        elements = new HeapId[ARR_SIZE];
        for (int i = 0; i < ARR_SIZE; i++) {
            mapHeapId[i] = 0;
        }
    }
    HeapId* getHeapId(SubClass* mSubClass) {
        intptr_t address = reinterpret_cast<intptr_t>(mSubClass);
        HeapId* temp = mapHeapId[address % ARR_SIZE];
        while (temp && temp->subClass != mSubClass)
            temp = temp->next;
        return temp;
    }
    void deleteMap(HeapId* mHeapId) {
        intptr_t address = reinterpret_cast<intptr_t>(mHeapId->subClass);
        int hash = address % ARR_SIZE;
        HeapId* temp = mapHeapId[hash];
        addToDeletedList(mHeapId);
        if (temp == mHeapId) {  // root
            mapHeapId[hash] = temp->next;
            // cout << "Head Deleted!\n";
            return;
        }
        if (temp == NULL) {  // root
            // cout << "Not Found!\n";
            return;
        }
        cout << 1 << endl;
        while (temp != 0 && temp->next != mHeapId)
            temp = temp->next;
        if (temp) {
            temp->next = mHeapId->next;
            mHeapId->next = NULL;
            // cout << "Node Deleted!\n";
        }
    }
    void addToDeletedList(HeapId* mHeapId) {
        if (deletedList == NULL) {
            deletedList = mHeapId;
        }
        mHeapId->next = deletedList;
        deletedList = mHeapId;
    }
    void insert(SubClass* mSubClass) {
        if (deletedList != NULL) {
            HeapId* newHeapId = deletedList;
            cout << newHeapId->subClass->getValue() << endl;
            deletedList = deletedList->next;
            newHeapId->subClass = mSubClass;
            intptr_t address = reinterpret_cast<intptr_t>(mSubClass);
            int hash = address % ARR_SIZE;
            newHeapId->next = mapHeapId[hash];
            elements[Heapindex[size]].Heapindex = size;
            Heapindex[size] = (newHeapId - elements);
            cout << size << " " << Heapindex[size] << endl;
            heapifyUp(size++);
            return;
        }
        elements[size].subClass = mSubClass;
        elements[size].Heapindex = size;
        intptr_t address = reinterpret_cast<intptr_t>(mSubClass);
        int hash = address % ARR_SIZE;
        elements[size].next = mapHeapId[hash];
        mapHeapId[hash] = &elements[size];
        Heapindex[size] = size;
        heapifyUp(size++);
    }
    void heapifyUp(int index) {
        int nextId = index,
            parent = (index - 1) / 2;
        if (nextId > 0) {
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
        HeapId* t = getHeapId(mSubClass);
        // cout << index << " " << Heapindex[index] << " " << elements[Heapindex[index]].subClass->getValue() << endl;
        if (t != NULL) {
            heapifyUp(t->Heapindex);
            heapifyDown(t->Heapindex);
        }
    }
    void Swap(int id1, int id2) {
        elements[Heapindex[id1]].Heapindex = id2;
        elements[Heapindex[id2]].Heapindex = id1;
        int t = Heapindex[id1];
        Heapindex[id1] = Heapindex[id2];
        Heapindex[id2] = t;
    }
    void erase(SubClass* mSubClass) {
        HeapId* t = getHeapId(mSubClass);
        if (t != NULL) {
            deleteMap(t);
            Swap(t->Heapindex, --size);
            heapifyDown(t->Heapindex);
        } else
            cout << "Not found!\n";
    }
    SubClass* pop() {
        deleteMap(&elements[Heapindex[0]]);
        Swap(0, --size);
        heapifyDown(0);
        cout << Heapindex[size] << " \t";
        return elements[Heapindex[size]].subClass;
    }
};
Heap mheap;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    auto st = high_resolution_clock::now();
    cout << "Started!" << endl;
    int n = 10;
    mheap.initForMaxHeap();
    for (int i = 0; i < n; i++) {
        MyData[i].setValue(rand() % 100);
        mheap.insert(&MyData[i]);
    }
    MyData[3].setValue(999);
    mheap.update(&MyData[3]);
    MyData[4].setValue(-999);
    mheap.update(&MyData[4]);
    mheap.erase(&MyData[2]);
    mheap.insert(&MyData[2]);
    // mheap.pop();
    mheap.erase(&MyData[3]);
    mheap.insert(&MyData[3]);
    cout << "Heap Started!" << endl;
    int s = mheap.getSize();
    for (int i = 0; i < s; i++) {
        SubClass* t = mheap.pop();
        cout << t->getValue() << " \t" << i << " \t" << MyData[i].getValue() << endl;
    }
    auto en = high_resolution_clock::now();
    double t = duration_cast<nanoseconds>(en - st).count();
    cout << t / 1e9;
    return 0;
}