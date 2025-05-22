#include <iostream>
using namespace std;
#define HASH_SIZE 100

class Node {
   public:
    unsigned long long key;
    int value;
    Node* next;
};

class HashMap {
   private:
    Node* heads[HASH_SIZE];
   public:
    HashMap() { clear(); }
    void clear() {
        for (int i = 0; i < HASH_SIZE; ++i)
            heads[i] = nullptr;
    }
    void insert(Node* newNode) {
        newNode->next = heads[newNode->key % HASH_SIZE];
        heads[newNode->key % HASH_SIZE] = newNode;
    }
    void erase(Node* node) {
        if (node != nullptr)
            erase(node->key);
    }
    void erase(unsigned long long key) {
        Node *cur = heads[key % HASH_SIZE], *prev;
        while (cur != nullptr && cur->key != key) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr)
            return;
        prev->next = cur->next;
    }
    Node* get(unsigned long long key) {
        Node* cur = heads[key % HASH_SIZE];
        while (cur != nullptr && cur->key != key)
            cur = cur->next;
        return cur;
    }
} hMap;

inline unsigned long long hashF(char* key) {
    register long long h = 0;
    for (register int i = 3; key[i]; i++) {
        h <<= 5;
        h |= key[i] & 0x1F;
    }
    return h;
}

void init() {
    hMap.clear();
}

int find(char key[]) {
    return hMap.get(hashF(key))->value;
}

void add(char key[], int data) {
    Node a = {hashF(key), data, nullptr};
    hMap.insert(&a);
}

int remove(char key[]) {
    hMap.erase(hashF(key));
}

int main(){
    HashMap h;
    Node a = {123, 1,nullptr},
        b = {223, 2,nullptr};
    h.insert(&a);
    h.insert(&b);
    cout << h.get(123)->value << endl;
    cout << h.get(223)->value << endl;
    h.erase(&a);
    cout << h.get(123)->value << endl;
    return 0;
}