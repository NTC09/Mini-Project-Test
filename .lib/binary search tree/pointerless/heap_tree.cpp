#include <iostream>

using namespace std;

const int MAX_SIZE = 0x20000 + 1;

int nodeNums = 0;

#define left(r) (r * 2 + 1)
#define right(r) (r * 2 + 2)
#define parent(r) ((r - 1) / 2)
class IndexTree {  // AVL tree
    class Node {
       public:
        int height;
        int value;
        Node(int value, int height) {
            this->value = value;
            this->height = height;
        }
    }* nodes[MAX_SIZE];
    int size;
    int root;

    void swapNode(int a, int b) {
        Node* t = nodes[a];
        nodes[a] = nodes[b];
        nodes[b] = t;
    }
    Node* leftNode(int root) {
        return nodes[left(root)];
    }
    Node* rightNode(int root) {
        return nodes[right(root)];
    }
    int insertInternal(int root, int value) {
        if (nodes[root] == 0) {
            nodes[root] = new Node(value, 1);
            return root;
        } else if (value < nodes[root]->value) {
            int left = insertInternal(left(root), value);
            if (left != left(root))
                swapNode(left(root), left);
        } else {
            int right = insertInternal(right(root), value);
            if (right != right(root))
                swapNode(right(root), right);
        }

        // Balancing
        nodes[root]->height = 1+ max(getHeight(left(root)), getHeight(right(root)));

        int valBalance = getHeight(left(root)) - getHeight(right(root));
        int newRoot;
        // left left
        if (valBalance > 1 && value < nodes[left(root)]->value)
            newRoot = rightRotate(root);

        // right right
        if (valBalance < -1 && value > nodes[right(root)]->value)
            newRoot = leftRotate(root);

        if (valBalance > 1 && value > nodes[left(root)]->value) {
            int rootLeft = leftRotate(left(root));
            if (rootLeft != left(root))
                swapNode(rootLeft, left(root));
            newRoot = rightRotate(root);
        }

        // 3.4. Right Left
        if (valBalance < -1 && value < nodes[right(root)]->value) {
            int rootRight = rightRotate(right(root));
            if (rootRight != right(root))
                swapNode(rootRight, right(root));
            newRoot = leftRotate(root);
        }
        if (root != newRoot)
            swapNode(root, newRoot);
        return root;
    }
    int rightRotate(int root) {
        int t = left(root);
        Node* x = nodes[t];

        nodes[left(root)] = nodes[right(t)];
        nodes[right(t)] = nodes[root];

        nodes[root]->height = max(getHeight(left(root)), getHeight(right(root)));
        nodes[t]->height = max(getHeight(left(t)), getHeight(right(t)));
        return root;
    }
    int leftRotate(int root) {
        int t = right(root);
        Node* x = nodes[t];

        nodes[right(root)] = nodes[left(t)];
        nodes[left(t)] = nodes[root];

        nodes[root]->height = max(getHeight(left(root)), getHeight(right(root)));
        nodes[t]->height = max(getHeight(left(t)), getHeight(right(t)));
        return root;
    }
    int getHeight(int root) {  // (O) = log2(index)
        if (root == 0)
            return 0;
        return nodes[root]->height;
    }
    int findInternal(int root, int value) {
        if (root == 0)
            return -1;
        else {
            if (nodes[root]->value == value)
                return value;
            else if (value < nodes[root]->value)
                return findInternal(left(root), value);
            else
                return findInternal(right(root), value);
        }
    }

   public:
    IndexTree() {
        root = 0;
        size = 0;
        for (int i = 0; i < MAX_SIZE; ++i)
            delete nodes[i];
    }
    void erase() {

    }
    void insert(int value) {
        ++size;
        root = insertInternal(root, value);
    }
    int find(int value) {
        return findInternal(root, value);
    }
};

int main() {
    IndexTree tree;
    tree.insert(8);
    tree.insert(4);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    cout << tree.find(9) << endl;
    cout << tree.find(8) << endl;
    cout << tree.find(4) << endl;
    return 0;
}