#include <malloc.h>
////////////////////////////////////////////////////////
//////////// TRIES ////////////////////////////////////

struct node {
    int cnt;
    int isLeaf;
    char ch;
    node* child[26];

    node() {
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
            cnt = 0;
            ch = 0;
            isLeaf = 0;
        }
    }
};

node* root;

node* DeleteTrie(node* n) {
    for (int i = 0; i < 26; i++) {
        if (n->child[i] != NULL) {
            DeleteTrie(n->child[i]);
        }
    }
    free(n);
    n = NULL;
    return n;
}

// Initialize the Trie
void init_trie() {
    if (root != NULL) {
        root = DeleteTrie(root);
    }
    root = (node*)calloc(1, sizeof(node));
}

// Insert a string "key" in trie
void Tries_insert(const char* key) {
    int i = 0;
    node* n = root;
    while (key[i] != 0) {
        int c = key[i] - 'a';
        if (n->child[c] == NULL) n->child[c] = (node*)calloc(1, sizeof(node));

        n->child[c]->ch = key[i];
        n->child[c]->cnt++;

        n = n->child[c];
        i++;
    }
    n->isLeaf += 1;
    root->cnt++;
}

// Returns true if whole "key" presents in trie, else false
bool Tries_search(const char* key) {
    int i = 0;
    node* n = root;
    while (key[i] != 0) {
        int c = key[i] - 'a';
        if (n->child[c] == NULL) {
            return false;
        }

        n = n->child[c];
        i++;
    }
    if (n->isLeaf > 0)
        return true;
    else
        return false;
}

// Returns number of keys having "key" as a prefix
int Tries_CountofkeysWithPrefix(const char* key) {
    int i = 0;
    node* n = root;
    while (key[i] != 0) {
        int c = key[i] - 'a';
        if (n->child[c] == NULL) {
            return 0;
        }

        n = n->child[c];
        i++;
    }
    return n->cnt;
}

bool DeleteKey(node* n, const char* key, int i) {
    if (n == NULL) return false;

    if (key[i] == 0) {
        if (n->isLeaf > 0) {
            n->isLeaf--;
            return true;
        } else
            return false;
    }

    int c = key[i] - 'a';
    if (n->child == NULL) return false;

    if (DeleteKey(n->child[c], key, i + 1)) {
        n->child[c]->cnt--;
        if (n->child[c] == 0) {
            free(n->child[c]);
            n->child[c] = NULL;
        }
        return true;
    }
    return false;
}

// deletes a key from trie
void Tries_deleteKey(const char* key) {
    int i = 0;
    DeleteKey(root, key, 0);
}