#include <iostream>

using namespace std;

#define MAX_NODE 100

struct Node {
    bool value; // true if there is a word here, can replace by a object/ pointer
    Node* ch[26]; // 26 charactor from a to z
};

Node* newNode() {
    static int count = 0;
    static Node nodes[MAX_NODE]; // use memory pool to limit memory
    for (int i = 0; i < 26; ++i) {
        nodes[count].ch[i] = nullptr;
    }
    nodes[count].value = false;
    return &nodes[count++];
}

Node* root = newNode();

bool add(const char* word) {
    Node* cur  = root;
    while (*word) {
        int v = *word - 'a'; // get index
        if (cur->ch[v] == nullptr)
            cur->ch[v] = newNode(); // create new branch
        cur = cur->ch[v];
        word++;
    }
    if (cur->value) return false; // word exist
    cur->value = true; // can do other stuff here
    return true;
}

bool del(const char* word) {
    Node* cur  = root;
    while (*word) {
        int v = *word - 'a'; // get index
        if (cur->ch[v] == nullptr)
            return false; // can't go further => no word
        cur = cur->ch[v];
        word++;
    }
    if (!cur->value) return false; // word not exist
    cur->value = false;
    return true;
}

int main() {
    cout << add("hel") << endl;
    cout << add("hell") << endl; 
    cout << add("hello") << endl;
    cout << add("hello") << endl; // fail
    cout << del("hello") << endl;
    cout << del("hello") << endl; // fail
    cout << del("he") << endl; // fail
}