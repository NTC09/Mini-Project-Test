#include "iostream"
using namespace std;

#define HASH_SIZE 1000

class Node {
   public:
    unsigned long long key;
    int value;
    Node* next;
    Node() {}
    Node(unsigned long long k,int v, Node * n) {
        key = k;
        value = v;
        next = n;
    }
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
        Node *cur = heads[key % HASH_SIZE], *prev = cur;
        while (cur != nullptr && cur->key != key) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr)
            return;
        if (cur == heads[key % HASH_SIZE])
            heads[key % HASH_SIZE] = cur->next;
        else
            prev->next = cur->next;
    }
    Node* get(unsigned long long key) {
        Node* cur = heads[key % HASH_SIZE];
        while (cur != nullptr && cur->key != key)
            cur = cur->next;
        return cur;
    }
} hMap;

int main() {
    hMap.insert(new Node(1001L, 99, nullptr));
    hMap.insert(new Node(10001L, 999, nullptr));
    hMap.insert(new Node(100001L, 9999, nullptr));
    hMap.erase(100001L);
    return 0;
}