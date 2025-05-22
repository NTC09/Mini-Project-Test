#include <iostream>
#include <memory.h>

using namespace std;

class Node {
   public:
    int left, right;
    friend class Tree;

    Node() {}
    
};

class Type : public Node {
    public:
    int value;
    bool operator<(const Type& mNode) const {
        return this->value < mNode.value;
    }
    bool operator==(const Type& mNode) const {
        return this->value == mNode.value;
    }
    void init() { left = right = -1; }
} nodes[100000];

// template <typename Type, typename _compare = smaller<Type>>
class Tree {
   private:
    int root;
    int size;

    Type getMax(int nodeId) {
        int cur = nodeId;
        while (nodes[cur].right != -1)
            cur = nodes[cur].right;
        return nodes[cur].value;
    }
    Type getMin(int nodeId) {
        int cur = nodeId;
        while (nodes[cur].left != -1)
            cur = nodes[cur].left;
        return nodes[cur].value;
    }
    int deleteNode(int nodeId, Type data) {
        if (nodeId == -1)
            return nodeId;
        if (data == nodes[nodeId]) {
            if (nodes[nodeId].left == -1) {
                int newId = nodes[nodeId].right;
                nodes[nodeId].init();
                return newId;
            }
            if (nodes[nodeId].right == -1) {
                int newId = nodes[nodeId].left;
                nodes[nodeId].init();
                return newId;
            }
            nodes[nodeId] = getMin(nodes[nodeId].right);
            nodes[nodeId].right = deleteNode(nodes[nodeId].right, nodes[nodeId]);
        } else if (data < nodes[nodeId].value)
            nodes[nodeId].left = deleteNode(nodes[nodeId].left, data);
        else
            nodes[nodeId].right = deleteNode(nodes[nodeId].right, data);
        return nodeId;
    }
    int insertInternal(int nodeId, Type data) {
        if (nodeId == -1) {
            if (size == 1000000)
                size = 0;
            nodes[size].init();
            nodes[size].value = data;
            return size++;
        }
        if (data < nodes[nodeId])
            nodes[nodeId].left = insertInternal(nodes[nodeId].left, data);
        else
            nodes[nodeId].right = insertInternal(nodes[nodeId].right, data);
        return nodeId;
    }
    void inOrder(int nodeId) {
        if (nodeId != -1) {
            inOrder(nodes[nodeId].left);
            cout << nodes[nodeId].value << endl;
            inOrder(nodes[nodeId].right);
        }
    }
    int findInternal(int nodeId, Type data) {
        if (nodeId == -1)
            return nodeId;
        if (data == nodes[nodeId].value)
            return nodeId;
        else if (data < nodes[nodeId].value)
            return findInternal(nodes[nodeId].left, data);
        else
            return findInternal(nodes[nodeId].right, data);
    }

   public:
    // Methods
    Tree() {
        root = -1;
        size = 0;
    }
    void clear() {
        root = -1;
        size = 0;
    }
    void insert(Type data) {
        root = insertInternal(root, data);
    }
    Type find(Type data) {
        int nodeId = findInternal(root, data);
        return nodes[nodeId].value;
    }
    void erase(Type data) {
        int id = findInternal(root, data);
        if (id != -1)
            root = deleteNode(root, data);
    }
    void inOrder() {
        inOrder(root);
    }
};
Tree tree;

int a[1000000];
int main() {
    int n = 16;
    for (int i = 0; i < n; i++) {
        a[i] = rand();
        tree.insert(a[i]);
    }
    /*for (int i = 0; i < n; i++) {
        tree.erase(a[i]);
    }
    for (int i = 0; i < 15; i++) {
        tree.insert(a[i]);
    }*/
    // cout << tree.nodes[0].value << endl;

    // tree.erase(2);
    // tree.erase(8);
    tree.inOrder();
    return 0;
}