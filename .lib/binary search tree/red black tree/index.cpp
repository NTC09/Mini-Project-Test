#include <iostream>

using namespace std;

template <typename subClass>
class Vectors {
   private:
    int __cap;
    int __size;
    subClass* __data;

   public:
    Vectors() {
        __size = 0;
        __cap = 10;
        __data = new subClass[10];
    }
    void clear() {
        __size = 0;
        if (__cap > 10) {
            __cap = 10;
            delete[] __data;
            __data = new subClass[10];
        }
    }
    void insert(subClass nSubClass) {
        if (__size >= __cap) {
            __cap *= 10;
            subClass* t = new subClass[__cap];
            for (int i = 0; i < __size; i++)
                t[i] = __data[i];
            delete[] __data;
            __data = t;
        }
        __data[__size++] = nSubClass;
    }
    subClass& operator[](int i) { return this->__data[i]; }
    subClass pop() { return __data[--__size]; }
    bool empty() { return __size == 0; }
    int size() { return this->__size; }
};

template <typename Type>
class bigger {
   public:
    //constexpr 
    bool operator()(const Type& a, const Type& b) const {
        return a > b;
    }
};

template <typename Type>
class smaller {
   public:
     bool operator()(const Type& a, const Type& b) const {
        return a < b;
    }
};

template <typename Type, typename compare = smaller<Type>>
class Tree {
   private:
    int root;
    int size;
    compare com;
    Vectors<int> delId;

    Type getMax(int nodeId) {
        int cur = nodeId;
        while (nodes[cur].right != -1)
            cur = nodes[cur].right;
        return nodes[cur].data;
    }
    Type getMin(int nodeId) {
        int cur = nodeId;
        while (nodes[cur].left != -1)
            cur = nodes[cur].left;
        return nodes[cur].data;
    }
    int deleteNode(int nodeId, Type data) {
        if (nodeId == -1)
            return nodeId;
        if (data == nodes[nodeId].data) {
            if (nodes[nodeId].left == -1) {
                int newId = nodes[nodeId].right;
                nodes[nodeId].init();
                delId.insert(nodeId);
                return newId;
            }
            if (nodes[nodeId].right == -1) {
                int newId = nodes[nodeId].left;
                nodes[nodeId].init();
                delId.insert(nodeId);
                return newId;
            }
            nodes[nodeId].data = getMin(nodes[nodeId].right);
            nodes[nodeId].right = deleteNode(nodes[nodeId].right, nodes[nodeId].data);
        } else if (data < nodes[nodeId].data)
            nodes[nodeId].left = deleteNode(nodes[nodeId].left, data);
        else
            nodes[nodeId].right = deleteNode(nodes[nodeId].right, data);
        return nodeId;
    }
    int insertInternal(int nodeId, Type &data) {
        if (nodeId == -1) {
            if (!delId.empty()) {
                
                int Id = delId.pop();
                nodes[Id].init();
                nodes[Id].data = data;
                return Id;
            }
            if (size == 1000000)
                size = 0;
            nodes[size].init();
            nodes[size].data = data;
            return size++;
        }
        if (com(data, nodes[nodeId].data))
            nodes[nodeId].left = insertInternal(nodes[nodeId].left, data);
        else
            nodes[nodeId].right = insertInternal(nodes[nodeId].right, data);
        return nodeId;
    }
    void inOrder(int nodeId) {
        if (nodeId != -1) {
            inOrder(nodes[nodeId].left);
            cout << nodes[nodeId].data << endl;
            inOrder(nodes[nodeId].right);
        }
    }
    int findInternal(int nodeId, Type data) {
        if (nodeId == -1)
            return nodeId;
        if (data == nodes[nodeId].data)
            return nodeId;
        else if (data < nodes[nodeId].data)
            return findInternal(nodes[nodeId].left, data);
        else
            return findInternal(nodes[nodeId].right, data);
    }

   public:
    class Node {
       public:
        Type data;
        int left, right;
        friend class Tree;
        bool operator<(const Node& mNode) const {
            return this->data < mNode.data;
        }
        Node() {}
        void init() { left = right = -1; }
    } nodes[1000000];
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
        return nodes[nodeId].data;
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
Tree<int> tree;

int a[1000000];
int main() {
    int n = 1000000;
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
    // cout << tree.nodes[0].data << endl;

    // tree.erase(2);
    // tree.erase(8);
    //tree.inOrder();
    return 0;
}