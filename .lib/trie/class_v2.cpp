#include <iostream>

using namespace std;

#define For(i, n) for (int i = 0; i < (n); i++)

class TrieNode {
   private:
    int value;
    bool have;
    TrieNode* next[26];
    void destroy(TrieNode* node) {
        node->have = false;
        For(i, 26) if (node->next[i] != 0)
            destroy(node->next[i]);
        node = 0;
    }

   public:
    TrieNode() {
        this->value = 0;
        this->have = false;
        For(i, 26)
            next[i] = nullptr;
    }
    TrieNode(int value) {
        this->have = false;
        For(i, 26)
            next[i] = 0;
        this->value = value;
    }
    void insert(const char* key, int value) {
        int i;
        TrieNode* cur = this;
        while (*key) {
            i = *key++ - 'a';
            if (cur->next[i] == nullptr)
                cur->next[i] = new TrieNode;
            cur = cur->next[i];
            if (*key == '\0') {
                cur->have = true;
                cur->value = value;
            }
        }
    }
    int search(const char* key) {
        int i;
        TrieNode* cur = this;
        while (*key) {
            i = *key++ - 'a';
            cur = cur->next[i];
            if (cur == nullptr)
                return -1;
            if (*key == '\0' && cur->have)
                return cur->value;
        }
        return -1;
    }
    void destroy() {
        For(i, 26) if (this->next[i] != nullptr)
            destroy(this->next[i]);
    }
    void erase(const char* key) {
        int i;
        TrieNode* cur = this;
        while (*key) {
            i = *key++ - 'a';
            if (cur->next[i] == 0)
                return;
            cur = cur->next[i];
            if (*key == '\0' && cur->have) {
                cur->have = false;
                return;
            }
        }
    }
    void erasePrefix(const char* key) {
        int i;
        TrieNode* cur = this;
        while (*key) {
            i = *key++ - 'a';
            if (cur->next[i] == nullptr)
                return;
            cur = cur->next[i];
            if (*key == '\0') {
                destroy(cur);
                return;
            }
        }
    }
} typedef Trie;

int main() {
    Trie trie;
    trie.insert("aaa", 10);
    trie.insert("aab", 20);
    trie.insert("abc", 30);
    trie.insert("abx", 40);

    cout << trie.search("aaa") << endl;
    cout << trie.search("aab") << endl;
    cout << trie.search("abc") << endl;
    cout << trie.search("abx") << endl;

    cout << trie.search("abb") << endl;
    cout << trie.search("aa") << endl;

    trie.erasePrefix("aa");
    cout << "erasePrefix" << endl;
    cout << trie.search("a") << endl;
    cout << trie.search("aab") << endl;
    cout << trie.search("abc") << endl;
    cout << trie.search("abx") << endl;
    cout << trie.search("abb") << endl;
    cout << trie.search("aa") << endl;

    cout << "Rebuild" << endl;
    trie.insert("a", 10);
    trie.insert("aab", 20);
    trie.insert("abc", 30);
    trie.insert("abx", 40);

    cout << trie.search("a") << endl;
    cout << trie.search("aab") << endl;
    cout << trie.search("abc") << endl;
    cout << trie.search("abx") << endl;
    cout << trie.search("abb") << endl;
    cout << trie.search("aa") << endl;

    cout << "Erase" << endl;
    trie.erase("a");
    cout << trie.search("a") << endl;
    trie.erase("abb");
    trie.erase("abx");
    cout << trie.search("abx") << endl;
    trie.destroy();
    cout << trie.search("a") << endl;
    cout << trie.search("aaa") << endl;
    cout << trie.search("abc") << endl;
    return 0;
}
