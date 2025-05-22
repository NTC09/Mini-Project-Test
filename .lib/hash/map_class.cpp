#include<bits/stdc++.h>

using namespace std;

class subClass {
public:
    int value;
}slist[100];

#define keyClass long long
//template <typename keyClass, typename subClass>
class HashMap {
    int capacity;
    int size;
    class Node {
        public:
        subClass* mSubclass;
        long long mKey;
        Node* next;
    } *nodes;
    Node** mapNode;
public:
    HashMap() {
        mapNode = new Node*[107];
        nodes = new Node[107];
        capacity = 107;
        size = 0;
        for (int i = 0; i < 107; i++) {
            mapNode = 0;
        }
    }
    void reset() {
        delete[] mapNode;
    }
    subClass& operator[](keyClass key) {
        int hash = key % capacity;
        Node* temp = mapNode[hash];

        while (temp != 0 && temp->mKey != key) {
            temp = temp->next;
        }
        if (temp == 0) {
        }
        return *temp->mSubclass;
    }
    void insert(keyClass key, subClass* mSubclass) {
        int hash = key % capacity;
        nodes[size].mSubclass = mSubclass;
        nodes[size].mKey = key;
        nodes[size].next = mapNode[hash];
        mapNode[hash] = &nodes[size++];
    }
};


int main() {
    auto start = chrono::high_resolution_clock::now();
    HashMap map;

    for (int i = 0;i < 10;i++) {
        slist[i].value = rand();
        map.insert(i, &slist[i]);
    }
    for (int i = 0;i < 10;i++) {
        cout << map[i].value << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Time: " << time / 1.0e9;
    return 0;
}