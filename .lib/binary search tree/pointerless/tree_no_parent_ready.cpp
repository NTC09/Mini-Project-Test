#include <iostream>

using namespace std;

#define SIZE 100000

int count = 0;

struct Node {
    int value;
    int left, right;
    bool operator<(Node& mNode) const {
        return this->value < mNode.value;
    }
    void copy(Node mNode) {
        this->left = mNode.left;
        this->right = mNode.right;
    }
    void init() { left = right = -1; }
} nodes[SIZE];

namespace Tree {
#define leftOf(id) nodes[id].left
#define rightOf(id) nodes[id].right
#define valueOf(id) nodes[id].value
#define compare(i1, i2) nodes[i1] < nodes[i2]

int root;

void clear() {
    root = -1;
}

void insert(int newId) {
    if (root == -1) {
        root = newId;
        return;
    }
    register int parent, cur, isleft;
    for (cur = root; cur != -1;) {
        parent = cur;
        if (compare(newId, cur))
            isleft = 1, cur = leftOf(cur);
        else
            isleft = 0, cur = rightOf(cur);
    }
    if (isleft)
        leftOf(parent) = newId;
    else
        rightOf(parent) = newId;
}

int erase(int value) {
    register int curId, preId = -1;
    for (curId = root; curId != -1;) {
        if (value < valueOf(curId))
            preId = curId, curId = leftOf(curId);
        else if (valueOf(curId) < value)
            preId = curId, curId = rightOf(curId);
        else
            break;
    }
    if (curId == -1)  // not found
        return -1;
    int newId;
    if (leftOf(curId) == -1 || rightOf(curId) == -1) {
        newId = (leftOf(curId) == -1) ? rightOf(curId) : leftOf(curId);
        if (preId == -1) {
            root = newId;
            return 0;
        }
        if (curId == leftOf(preId))
            leftOf(preId) = newId;
        else
            rightOf(preId) = newId;
    } else {
        int pNew = -1;
        for (newId = rightOf(curId); leftOf(newId) != -1;) {
            pNew = newId;
            newId = leftOf(newId);
        }
        if (pNew != -1)
            leftOf(pNew) = rightOf(newId);
        else
            rightOf(curId) = rightOf(newId);
        valueOf(curId) = valueOf(newId);
    }
    return 0;
}

int higher(int value) {  // >
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (value < valueOf(cur)) {
            id = cur;
            cur = leftOf(cur);
        } else
            cur = rightOf(cur);
    }
    return id == -1 ? id : valueOf(id);
}

int ceiling(int value) {  // >=
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (valueOf(cur) < value) {
            cur = rightOf(cur);
        } else {
            id = cur;
            cur = leftOf(cur);
        }
    }
    return id == -1 ? id : valueOf(id);
}

int lower(int value) {  // <
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (valueOf(cur) < value) {
            id = cur;
            cur = rightOf(cur);
        } else
            cur = leftOf(cur);
    }
    return id == -1 ? id : valueOf(id);
}

int floor(int value) {  // <=
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (value < valueOf(cur)) {
            cur = leftOf(cur);
        } else {
            id = cur;
            cur = rightOf(cur);
        }
    }
    return id == -1 ? id : valueOf(id);
}

int find(int value) {
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (value < valueOf(cur)) {
            cur = leftOf(cur);
        } else {
            id = cur;
            cur = rightOf(cur);
        }
    }
    return id == -1 ? id : (valueOf(id) < value ? -1 : valueOf(id));
}

int getMax(int curId) {
    int cur;
    for (cur = curId; rightOf(cur) != -1;)
        cur = rightOf(cur);
    return cur;
}
int getMin(int curId) {
    int cur;
    for (cur = curId; leftOf(cur) != -1;)
        cur = leftOf(cur);
    return cur;
}
void inOrder(int id) {
    if (id != -1) {
        inOrder(leftOf(id));
        cout << valueOf(id) << endl;
        inOrder(rightOf(id));
    }
}
};  // namespace Tree

void add() {
    nodes[count].init();
    nodes[count].value = rand() % 27;
    Tree::insert(count++);
}

int main() {
    Tree::clear();
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
    Tree::erase(10);
    Tree::erase(11);
    Tree::erase(25);
    Tree::inOrder(0);
    cout << endl
         << Tree::ceiling(25) << endl
         << Tree::  floor(25) << endl
         << Tree:: higher(24) << endl
         << Tree::  lower(24) << endl
         << Tree::find(24);
    return 0;
}