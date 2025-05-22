#define HASH_SIZE 100007

class Node {
   public:
    unsigned long long key;
    Node* next;
    Node() { next = nullptr; }
};

class HashMap {
   private:
    Node* heads[HASH_SIZE];
    void erase(unsigned long long key) {
        Node *cur = heads[key % HASH_SIZE], *prev;
        while (cur != nullptr && cur->key != key) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr)
            return;
        else if (cur == heads[key % HASH_SIZE]) {
            heads[key % HASH_SIZE] = cur->next;
        } else {
            prev->next = cur->next;
        }
    }

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

    Node* get(unsigned long long key) {
        Node* cur = heads[key % HASH_SIZE];
        while (cur != nullptr && cur->key != key)
            cur = cur->next;
        return cur;
    }
};