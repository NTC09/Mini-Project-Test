#include <cstdint>
#include <iostream>
#include <map>

using namespace std;

template <typename keyClass, typename subClass>
class HashMap {
   private:
    int capacity;
    int size;

   public:
    class Node {
       public:
        subClass* mSubclass;
        keyClass* mKey;
        Node* next;
    }* mapNode;
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
        this();
    }
    void insert(keyClass* key, subClass* newSubClass) {
        mapNode[size].mSubclass = newSubClass;
        mapNode[size].mKey = key;
    }
    void increase() {
        capacity -= 7;
        capacity *= 100;
        capacity += 7;
        Node* temp = new Node[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = mapNode[i];
        }
        delete[] mapNode;
        mapNode = temp;
    }
    subClass* operator[](keyClass* key) {
        unsigned int keyAddr = (unsigned int)key;
        int hash = keyAddr % capacity;
        Node* temp = &mapNode[hash];
        while (temp != 0 && temp->mKey != key) {
            temp = temp->next;
        }
        if (temp == 0) {
        }
        return temp->mSubclass;
    }
};

/*struct Map {
    int index[50013];
    Car& operator[](int num) {
        register int h = num % 50013;
        register int id = index[h];
        while (id > 0 && car[id].CarNumber != num)
            id = car[id].next;
        if (!id) {
            car[carCount] = {num, 0, 0, 0, false, 0};
            car[carCount].next = index[h];
            index[h] = carCount;
            id = carCount++;
        }
        return car[id];
    }
    void reset() {
        FOR(i, 0, 50013)
        index[i] = 0;
    }
} CarList;*/

int main() {
    HashMap<int, int> map;
    int key1 = 1, value1 = 10;
    map.insert(&key1, &value1);
    *map[&key1] = 300;
    cout << *map[&key1];
    return 0;
}