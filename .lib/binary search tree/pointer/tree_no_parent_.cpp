#include <iostream>

using namespace std;

#define SIZE 100000

int count = 0;

struct Node {
    int value;
    Node *left, *right;
    bool operator<(Node& mNode) const {
        return this->value < mNode.value;
    }
    void copy(Node mNode) {
        this->left = mNode.left;
        this->right = mNode.right;
    }
    void init() { left = right = nullptr; }
} nodes[SIZE];

#define compare(n1, n2) n1->value < n2->value
#define R register

struct Tree {
    Node* root;

    void clear();
    void insert(Node* newNode);
    void erase(int value);
    void erase(Node* node, Node* prev);
    int higher(int value);
    int ceiling(int value);
    int lower(int value);
    int floor(int value);
    int find(int value);
    int getMax(Node* curNode);
    int getMin(Node* curNode);
    void inOrder(Node* id);
    void printTree();
    void printTreeHelper(Node* root, int space);
};

void Tree::clear() {
    root = nullptr;
}

void Tree::insert(R Node* newNode) {
    if (root == nullptr) {
        root = newNode;
        return;
    }
    for (R Node *parent, *cur = root;;) {
        parent = cur;
        if (compare(newNode, cur)) {
            cur = cur->left;
            if (cur == nullptr) {
                parent->left = newNode;
                return;
            }
        } else {
            cur = cur->right;
            if (cur == nullptr) {
                parent->right = newNode;
                return;
            }
        }
    }
}

void Tree::erase(R int value) {
    R Node *cur, *node = nullptr, *parent = nullptr, *prev = nullptr;
    for (cur = root; cur != nullptr;) {
        if (value < cur->value)
            parent = cur, cur = cur->left;
        else {
            prev = parent;
            parent = cur;
            node = cur;
            cur = cur->right;
        }
    }
    if (node == nullptr || node->value < value)  // not found
        return;
    erase(node, prev);
}

void Tree::erase(R Node* node, Node* prev) {
    if (node->left == nullptr || node->right == nullptr) {
        R Node* cur = (node->left == nullptr) ? node->right : node->left;
        if (prev == nullptr) {
            root = cur;
            return;
        }
        if (node == prev->left)
            prev->left = cur;
        else
            prev->right = cur;
    } else {
        R Node *parent = nullptr, *cur;
        for (cur = node->right; cur->left != nullptr;) {
            parent = cur;
            cur = cur->left;
        }
        if (prev == nullptr) {
            root = cur;
        } else {
            if (node == prev->left)
                prev->left = cur;
            else
                prev->right = cur;
        }
        if (parent != nullptr) {  // cur is not right of cur
            parent->left = cur->right;
            cur->right = node->right;
        }
        cur->left = node->left;
    }
}

int Tree::higher(R int value) {  // >
    R Node *res = nullptr, *cur = root;
    for (; cur != nullptr;)
        if (value < cur->value)
            res = cur, cur = cur->left;
        else
            cur = cur->right;
    return res == nullptr ? -1 : res->value;
}

int Tree::ceiling(R int value) {  // >=
    R Node *res = nullptr, *cur = root;
    for (; cur != nullptr;)
        if (cur->value < value)
            cur = cur->right;
        else
            res = cur, cur = cur->left;
    return res == nullptr ? -1 : res->value;
}

int Tree::lower(int value) {  // <
    R Node *res = nullptr, *cur = root;
    for (; cur != nullptr;)
        if (cur->value < value)
            res = cur, cur = cur->right;
        else
            cur = cur->left;
    return res == nullptr ? -1 : res->value;
}

int Tree::floor(int value) {  // <=
    R Node *res = nullptr, *cur = root;
    for (; cur != nullptr;)
        if (value < cur->value)
            cur = cur->left;
        else
            res = cur, cur = cur->right;
    return res == nullptr ? -1 : res->value;
}

int Tree::find(int value) {
    R int res = floor(value);
    return res;
}

int Tree::getMax(Node* curId) {
    Node* cur;
    for (cur = curId; cur->right != nullptr;)
        cur = cur->right;
    return cur->value;
}
int Tree::getMin(Node* curId) {
    Node* cur;
    for (cur = curId; cur->left != nullptr;)
        cur = cur->left;
    return cur->value;
}
void Tree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->value << endl;
        inOrder(node->right);
    }
}

void Tree::printTreeHelper(Node* root, int space) {
    int i;
    if (root != nullptr) {
        space = space + 4;
        printTreeHelper(root->right, space);
        cout << endl;
        for (i = 4; i < space; i++) {
            cout << " ";
        }
        cout << root->value << endl;
        printTreeHelper(root->left, space);
    }
}

void Tree::printTree() {
    printTreeHelper(root, 0);
}

Tree tree;

void add() {
    nodes[count].init();
    nodes[count].value = rand() % 100007;
    tree.insert(&nodes[count++]);
}

int main() {
    tree.clear();
    int n = 16;
    for (int i = 0; i < n; i++)
        add();
    // Tree::deleteNode(4);
    // Tree::deleteNode(5);
    // cout << "Deleted " << nodes[4].value << endl;
    // cout << "Deleted " << nodes[5].value << endl;
    // add();
    // add();
    // add();
    // add();
    tree.erase(41);
    tree.erase(62);
    tree.erase(63);
    //tree.printTree();
    cout << endl
         << tree.ceiling(25) << endl
         << tree.floor(25) << endl
         << tree.higher(24) << endl
         << tree.lower(24) << endl
         << tree.find(29);
    return 0;
}