#include <iostream>

using namespace std;

#define SIZE 100000

int count = 0;

struct Node {
    int value;
    int height;
    int left, right, parent;
    bool operator<(Node& mNode) const {
        return this->value < mNode.value;
    }
    void copy(Node mNode) {
        this->left = mNode.left;
        this->right = mNode.right;
    }
    void init() {
        left = right = parent = -1;
        height = 1;
    }
};
Node dummy;  // -1
Node nodes[SIZE];

namespace Tree {  // AVL tree
#define leftOf(id) nodes[id].left
#define rightOf(id) nodes[id].right
#define valueOf(id) nodes[id].value
#define parentOf(id) nodes[id].parent
#define heightOf(id) nodes[id].height
#define compare(i1, i2) nodes[i1] < nodes[i2]
#define MAX(a, b) ((a) < (b) ? (b) : (a))

int root;

void clear() {
    root = -1;
}

int rightRotate(int y) {
    int x = leftOf(y);
    int T = rightOf(x);
    rightOf(x) = y;
    parentOf(x) = parentOf(y);
    parentOf(y) = x;
    leftOf(y) = T;
    if (T != -1)
        parentOf(T) = y;
    heightOf(y) = 1 + MAX(heightOf(leftOf(y)), heightOf(rightOf(y)));
    heightOf(x) = 1 + MAX(heightOf(leftOf(x)), heightOf(rightOf(x)));
    return x;
}

int leftRotate(int x) {
    int y = rightOf(x);
    int T = leftOf(y);
    leftOf(y) = x;
    parentOf(y) = parentOf(x);
    parentOf(x) = y;
    rightOf(x) = T;
    if (T != -1)
        parentOf(T) = x;
    heightOf(x) = 1 + MAX(heightOf(leftOf(x)), heightOf(rightOf(x)));
    heightOf(y) = 1 + MAX(heightOf(leftOf(y)), heightOf(rightOf(y)));
    return y;
}

int getBalance(int root) {
    if (root == -1)
        return 0;
    return heightOf(leftOf(root)) - heightOf(rightOf(root));
}

int balance(int root) {
    if (root == -1)
        return root;
    heightOf(root) = 1 + MAX(heightOf(leftOf(root)), heightOf(rightOf(root)));
    int balance = getBalance(root);
    int blLeft = getBalance(leftOf(root));
    int blRight = getBalance(rightOf(root));

    if (balance > 1) {
        if (blLeft >= 0) {  // left left
            return rightRotate(root);
        } else {  // left right
            leftOf(root) = leftRotate(leftOf(root));
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (blRight <= 0) {  // right right
            return leftRotate(root);
        } else {  // right left
            rightOf(root) = rightRotate(rightOf(root));
            return leftRotate(root);
        }
    }
    return root;
}

int insert(int root, int newId) {
    if (root == -1) {
        return newId;
    }
    if (compare(newId, root)) {
        leftOf(root) = insert(leftOf(root), newId);
        parentOf(leftOf(root)) = root;
    } else {
        rightOf(root) = insert(rightOf(root), newId);
        parentOf(rightOf(root)) = root;
    }
    return balance(root);
}

int erase(int value) {
    register int cur, root;
    for (root = Tree::root; root != -1;) {
        if (value < valueOf(root)) {
            root = leftOf(root);
        } else {
            cur = root;
            root = rightOf(root);
        }
    }
    if (cur == -1 || valueOf(cur) != value)  // not found
        return -1;
    root = parentOf(cur);
    register int newId;
    if (leftOf(cur) == -1 || rightOf(cur) == -1) {
        newId = (leftOf(cur) == -1) ? rightOf(cur) : leftOf(cur);
        if (root == -1) {
            root = newId;
            return root;
        }
        if (cur == leftOf(root))
            leftOf(root) = newId;
        else
            rightOf(root) = newId;
    } else {
        int pNew = -1;
        for (newId = rightOf(cur); leftOf(newId) != -1;) {
            pNew = newId;
            newId = leftOf(newId);
        }
        if (pNew != -1)
            leftOf(pNew) = rightOf(newId);
        else
            rightOf(cur) = rightOf(newId);
        valueOf(cur) = valueOf(newId);
    }
    return balance(root);
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

int getMax(int root) {
    int cur;
    for (cur = root; rightOf(cur) != -1;)
        cur = rightOf(cur);
    return cur;
}
int getMin(int root) {
    int cur;
    for (cur = root; leftOf(cur) != -1;)
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
void inOrder(int id, int min, int max) {
    if (id != -1) {
        if (valueOf(id) < min) {
            inOrder(rightOf(id), min, max);
            return;
        }
        inOrder(leftOf(id), min, max);
        if (max < valueOf(id)) {
            return;
        }
        cout << valueOf(id) << endl;
        inOrder(rightOf(id), min, max);
    }
}
void printTree(int root, int space) {
    if (root != -1) {
        printTree(rightOf(root), space + 6);
        cout << endl;
        for (int i = 0; i < space; ++i)
            cout << " ";
        cout << valueOf(root) << endl;
        printTree(leftOf(root), space + 6);
    }
}

// public
void insert(int newId) {
    root = insert(root, newId);
}

void printTree(int root) {
    printTree(root, 0);
}
};  // namespace Tree

void add() {
    nodes[count].init();
    nodes[count].value = rand() % 107;
    cout << nodes[count].value << " ";
    Tree::insert(count++);
}

int main() {
    dummy.init();
    dummy.height = 0;
    Tree::clear();
    int n = 16;
    for (int i = 0; i < n; i++) {
        add();
        // Tree::printTree(0);
        // cout << "-----------------------------------------------------\n";
    }
    cout << "-----------------------------------------------------\n";
    // Tree::deleteNode(4);
    // Tree::deleteNode(5);
    // cout << "Deleted " << nodes[4].value << endl;
    // cout << "Deleted " << nodes[5].value << endl;
    // add();
    // add();
    // add();
    // add();
    // Tree::erase(69);
    // Tree::erase(0);
    // Tree::erase(41);
    Tree::printTree(0);
    Tree::inOrder(0, 40, 63);
    // Tree::inOrder(0);
    cout << endl
         << Tree::ceiling(5) << endl
         << Tree::floor(5) << endl
         << Tree::higher(10) << endl
         << Tree::lower(10) << endl
         << Tree::find(24);
    return 0;
}