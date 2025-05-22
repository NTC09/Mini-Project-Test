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
} *MyData;

//template <typename SubClass>
class Heap {
private:
    static const int ARR_SIZE = 100007;
    class Node {
    public:
        int heapid;
        SubClass* key;
        Node* next;
        bool operator<(Node& node) const {
            return *(this->key) < *(node.key);
        }
        int getKey() {
            return (int)((void*)this->key);
        }
    } node[ARR_SIZE];
    Node* htree[ARR_SIZE];
    Node* hmap[ARR_SIZE];
    int size;
    // int capacity;
    bool isMaxHeap;
    bool comp(int i1, int i2) {
        return (*htree[i1] < *htree[i2]) == isMaxHeap;
    }
public:
    static int test;
    Heap() {
        size = 0;
    }
    int convert(SubClass* s) {
        void* p = s;
        return (int)p;
    }
    void init() {
        size = 0;
        for (int i = 0; i < ARR_SIZE; i++) {
            hmap[i] = 0;
        }
    }
    void initForMaxHeap() {
        init();
        isMaxHeap = true;
    }
    void initForMinHeap() {
        init();
        isMaxHeap = false;
    }
    /**
     * @brief Get the index in htree
     *
     * @param mSubClass pointer to object
     * @return int
     */
    Node* getNode(SubClass* mSubClass) {
        int key = convert(mSubClass);
        Node* temp = hmap[key % ARR_SIZE];
        while (temp != 0 && temp->getKey() != key)
            temp = temp->next;
        return temp;
    }
    void deleteMap(int index) {
        int key = node[index].getKey();
        int hash = key % ARR_SIZE;
        Node* temp = hmap[hash];
        if (temp->heapid == index) {  // head
            hmap[hash] = temp->next;
            cout << "Head Deleted!\n";
            return;
        }
        Node* prev;
        while (temp != 0 && temp->heapid != index) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != 0) {
            prev->next = temp->next;
            cout << "Node Deleted!\n";
        }
    }
    void insert(SubClass* mSubClass) {
        Node* n = getNode(mSubClass); // if the node deleted but still in node[]
        if (n == 0)
            n = &node[size];
        else
            cout << "Re insert\n";
        // insert to map
        n->key = mSubClass;
        n->heapid = size;
        int key = convert(mSubClass);
        int hash = key % ARR_SIZE;
        n->next = hmap[hash];
        hmap[hash] = n;
        htree[size] = n;
        heapifyUp(size++);
        //cout << key << " " << hash << endl;
    }
    void heapifyUp(int index) {
        int nextId = index,
            parent = (index - 1) / 2;
        if (parent >= 0)
            if (comp(parent, nextId))
                nextId = parent;
        if (nextId != index) {
            Swap(nextId, index);
            heapifyUp(nextId);
        }
    }
    void heapifyDown(int index) {
        int nextId = index,
            left = 2 * index + 1,
            right = 2 * index + 2;
        if (left < size)
            if ((comp(nextId, left)))
                nextId = left;
        if (right < size)
            if ((comp(nextId, right)))
                nextId = right;
        if (nextId != index) {
            Swap(nextId, index);
            heapifyDown(nextId);
        }
    }
    void update(SubClass* mSubClass) {
        Node* n = getNode(mSubClass);
        if (n->heapid >= size) {
            cout << "Not found!\n";
            return;
        }
        cout << "Update: " << n->heapid << " "
            << n->key->getValue() << endl;
        heapifyUp(n->heapid);
        heapifyDown(n->heapid);
    }
    void Swap(int id1, int id2) {
        if (id1 == id2)
            return;
        Node* t = htree[id1];
        htree[id1] = htree[id2];
        htree[id2] = t;
        htree[id1]->heapid = id1;
        htree[id2]->heapid = id2;
    }
    void erase(SubClass* mSubClass) {
        Node* n = getNode(mSubClass);
        if (n->heapid == -1) {
            cout << "Not found!\n";
            return;
        }
        cout << "Erasing: " << n->heapid << " "
            << n->key->getValue() << endl;
        Swap(n->heapid, --size);
        heapifyDown(n->heapid);
        //deleteMap(index);
    }
    SubClass* pop() {
        if (size == 0)
            return NULL;
        Swap(0, --size);
        heapifyDown(0);
        return htree[size]->key;
    }
    bool empty() {
        return size == 0;
    }
    bool full() {
        return size == ARR_SIZE;
    }
};
int Heap::test = 0;
Heap mheap, heap2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    MyData = new SubClass[MAX_ARR];
    auto st = high_resolution_clock::now();
    cout << "Started!" << endl;
    int n = 10;
    mheap.initForMaxHeap();
    mheap.test = 11;
    heap2.test = 22;
    //heap2.initForMinHeap();
    for (int i = 0; i < n; i++) {
        MyData[i].setValue(i * 10 + 1);
        mheap.insert(&MyData[i]);
    }
    /*MyData[3].setValue(9999);
    mheap.update(&MyData[3]);
    MyData[4].setValue(-999);
    mheap.update(&MyData[4]);*/
    cout << "Heap Started!" << endl;
    mheap.getNode(&MyData[2]);
    mheap.erase(&MyData[2]);
    mheap.update(&MyData[2]);
    mheap.insert(&MyData[2]);
    MyData[2].setValue(9999);
    mheap.update(&MyData[2]);
    for (int i = 0; !mheap.empty(); i++) {
        SubClass* t = mheap.pop();
        /*if (t == 0)
            continue;*/
        cout << t->getValue() << " \t" << i << " \t" << MyData[i].getValue() << endl;
    }
    cout << mheap.test << endl;
    cout << "Heap End!" << endl;
    auto en = high_resolution_clock::now();
    double t = duration_cast<nanoseconds>(en - st).count();
    cout << t / 1e9;
    return 0;
}