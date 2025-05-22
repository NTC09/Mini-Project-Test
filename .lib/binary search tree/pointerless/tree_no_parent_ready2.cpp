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

#define leftOf(id) nodes[id].left
#define rightOf(id) nodes[id].right
#define valueOf(id) nodes[id].value
#define compare(i1, i2) nodes[i1] < nodes[i2]

struct Tree {
    int root;

    void clear();
    void insert(int newId);
    int erase(int value);
    int higher(int value);
    int ceiling(int value);
    int lower(int value);
    int floor(int value);
    int find(int value);
    int getMax(int curId);
    int getMin(int curId);
    void inOrder(int id);
    void printTree();
    void printTreeHelper(int root, int space);
};

void Tree::clear() {
    root = -1;
}

void Tree::insert(int newId) {
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

int Tree::erase(int value) {
    int id, curId = -1, parent = -1, preId = -1;
    for (id = root; id != -1;) {
        if (value < valueOf(id))
            parent = id, id = leftOf(id);
        else {
            preId = parent;
            parent = id;
            curId = id;
            id = rightOf(id);
        }
    }
    if (curId == -1 || valueOf(curId) != value)  // not found
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
        parent = -1;
        for (newId = rightOf(curId); leftOf(newId) != -1;) {
            parent = newId;
            newId = leftOf(newId);
        }
        if (preId == -1) {
            root = newId;
        } else {
            if (curId == leftOf(preId))
                leftOf(preId) = newId;
            else
                rightOf(preId) = newId;
        }
        leftOf(newId) = leftOf(curId);
        if (parent != -1) { // newId is not right of cur
            leftOf(parent) = rightOf(newId);
            rightOf(newId) = rightOf(curId);
        }
    }
    return 0;
}

int Tree::higher(int value) {  // >
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

int Tree::ceiling(int value) {  // >=
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

int Tree::lower(int value) {  // <
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

int Tree::floor(int value) {  // <=
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

int Tree::find(int value) {
    register int id = floor(value);
    return id == -1 ? id : (valueOf(id) < value ? -1 : valueOf(id));
}

int Tree::getMax(int curId) {
    int cur;
    for (cur = curId; rightOf(cur) != -1;)
        cur = rightOf(cur);
    return cur;
}
int Tree::getMin(int curId) {
    int cur;
    for (cur = curId; leftOf(cur) != -1;)
        cur = leftOf(cur);
    return cur;
}
void Tree::inOrder(int id) {
    if (id != -1) {
        inOrder(leftOf(id));
        cout << valueOf(id) << endl;
        inOrder(rightOf(id));
    }
}

void Tree::printTreeHelper(int root, int space) {
    int i;
    if (root != -1) {
        space = space + 4;
        printTreeHelper(rightOf(root), space);
        cout << endl;
        for (i = 4; i < space; i++) {
            cout << " ";
        }
        cout << valueOf(root) << endl;
        printTreeHelper(leftOf(root), space);
    }
}

void Tree::printTree() {
    printTreeHelper(root, 0);
}

Tree tree;

void add() {
    nodes[count].init();
    nodes[count].value = rand() % 107;
    tree.insert(count++);
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
    tree.printTree();
    cout << endl
         << tree.ceiling(25) << endl
         << tree.floor(25) << endl
         << tree.higher(24) << endl
         << tree.lower(24) << endl
         << tree.find(29);
    return 0;
}