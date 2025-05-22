#define MAX_NODE 120000
#define R register

struct Node {
    int has;
    int count;
    Node *ch[26];
};

int count = 0;
Node *newNode() {
    static Node nodes[MAX_NODE];  // use memory pool to limit memory
    for (R int i = 0; i < 26; ++i) {
        nodes[count].ch[i] = nullptr;
    }
    nodes[count].has = 0;
    nodes[count].count = 0;
    return &nodes[count++];
}

Node *root;

void init_trie() {
    count = 0;
    root = newNode();
}

void Tries_insert(R const char *key) {
    R Node *cur = root;
    while (*key) {
        R int i = *key - 'a';
        if (cur->ch[i] == nullptr) cur->ch[i] = newNode();
        cur = cur->ch[i];
        cur->count++;
        ++key;
    }
    // ++cur->count; ??
    cur->has++;
}

bool Tries_search(R const char *key) {
    R Node *cur = root;
    while (*key) {
        R int i = *key - 'a';
        if (cur->ch[i] == nullptr) return false;
        cur = cur->ch[i];
        ++key;
    }
    return cur->has > 0;
}

int Tries_CountofkeysWithPrefix(R const char *key) {
    R Node *cur = root;
    while (*key) {
        R int i = *key - 'a';
        if (cur->ch[i] == nullptr) return 0;
        cur = cur->ch[i];
        ++key;
    }
    return cur->count;
}

void Tries_deleteKey(R const char *key) {
    R Node *cur = root;
    if (!Tries_search(key)) return;
    while (*key) {
        R int i = *key - 'a';
        cur = cur->ch[i];
        --cur->count;
        ++key;
    }
    //--cur->count; ??
    --cur->has;
}
