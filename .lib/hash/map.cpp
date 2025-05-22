#include<bits/stdc++.h>

using namespace std;

#define keyClass int
#define subClass int

//template <typename keyClass, typename subClass>
class HashMap {
    int capacity;
    int size;
    class Node {
        subClass* mSubclass;
        keyClass* mKey;
        Node* next;
        friend class HashMap;
    } *mapNode;
public:
    HashMap() {
        mapNode = new Node[107];
        capacity = 107;
        size = 0;
        for (int i = 0; i < 107; i++) {
            mapNode = 0;
        }
    }
    void reset() {
        delete[] mapNode;
    }
    void insert(subClass* newSubClass) {

    }
    subClass& operator[](keyClass key) {
        intptr_t keyAddr = reinterpret_cast<intptr_t>(key);
        int hash = keyAddr % capacity;
        Node* temp = &mapNode[hash];
        
        while (temp != 0 && *temp->mKey != key) {
            temp = temp->next;
        }
        if (temp == 0) { // Add new
            mapNode[size].mSubclass = &key;
            
        }
        return *temp->mSubclass;
    }
};


int main() {
    auto start = chrono::high_resolution_clock::now();
    HashMap map;
    for (int i = 0;i < 10;i++) {
        map[i] = i + 1;
    }
    for (int i = 0;i < 10;i++) {
        cout << map[i] << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Time: " << time / 1.0e9;
    return 0;
}