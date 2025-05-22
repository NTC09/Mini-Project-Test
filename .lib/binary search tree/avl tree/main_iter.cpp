#include <iostream>
#include <set>

using namespace std;

#ifndef NULL
#define NULL 0LL
#endif

class Type {
   public:
    int data;
    bool operator<(const Type& type) const {
        return this->data < type.data;
    }
    friend ostream& operator<<(ostream& ou, Type& t) {
        ou << t.data;
        return ou;
    }
};

// typedef int Type;

// template <typename Type>
struct smaller {
    bool operator()(const Type& t1, const Type& t2) {
        return t1 < t2;
    }
};

typedef smaller compare;
// template <typename Type, typename compare = smaller<Type>>
class AVLTree {
   private:
    class Node {
       public:
        Node* left;
        Node* right;
        Node* parent;
        int height;
        Type data;

        Node() {
            left = right = parent = nullptr;
            height = 1;
        }
        Node(Type newData) {
            left = right = parent = nullptr;
            data = newData;
            height = 1;
        }
    };

    class iterator {
        using value_type = Type;
        using pointer = Type*;

       private:
        Node* node;

       public:
        //friend class AVLTree;
        iterator() {}
        iterator(Node* node) {
            this->node = node;
        }
        value_type operator*() const { return node->data; }
        pointer operator->() { return &node->data; }
        iterator& operator++() {
            this->node = getNext(this->node, this->node);
            return *this;
        }
        iterator& operator++(int) {
            this->node = getNext(this->node, this->node);
            return *this;
        }
        bool operator!=(const iterator& i) const {
            return this->node != i.node;
        }
    };

    Node* root;
    compare com;
    unsigned long long _size;

    Node* insertInternal(Node* root, Type& newData) {
        if (root == nullptr) {
            return new Node(newData);
        } else {
            if (com(newData, root->data)) {
                root->left = insertInternal(root->left, newData);
                root->left->parent = root;
            } else {
                root->right = insertInternal(root->right, newData);
                root->right->parent = root;
            }
        }
        return balancing(root);
    }
    Node* deleteNode(Node* root, Type data) {
        if (root == nullptr)
            return root;
        if (com(data, root->data)) {
            root->left = deleteNode(root->left, data);
            if (root->left != nullptr)
                root->left->parent = root;
        } else if (com(root->data, data)) {
            root->right = deleteNode(root->right, data);
            if (root->right != nullptr)
                root->right->parent = root;
        } else {
            if ((root->left == nullptr) ||
                (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {  // No child
                    temp = root;
                    root = nullptr;
                } else {  // One child case
                    Node* p = root->parent;
                    *root = *temp;
                    root->parent = p;
                }
                delete temp;
                --_size;
            } else {  // Two child case
                Node* temp = getMinOf(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
                if (root->right != nullptr)
                    root->right->parent = root;
            }
        }
        return balancing(root);
    }
    Node* balancing(Node* root) {
        if (root == nullptr)
            return root;
        root->height = 1 + MAX(height(root->left), height(root->right));
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)  // Left left Case
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {  // Left Right Case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)  // Right Right Case
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {  // Right Left Case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    static Node* getMinOf(Node* root) {
        if (root == nullptr || root->left == nullptr)
            return root;
        return getMinOf(root->left);
    }
    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) -
               height(N->right);
    }
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        x->parent = y->parent;
        y->parent = x;
        if (T2 != nullptr) {
            T2->parent = y;
        }
        y->height = 1 + MAX(height(y->left), height(y->right));
        x->height = 1 + MAX(height(x->left), height(x->right));
        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        y->parent = x->parent;
        x->parent = y;
        if (T2 != NULL) {
            T2->parent = x;
        }
        x->height = 1 + MAX(height(x->left), height(x->right));
        y->height = 1 + MAX(height(y->left), height(y->right));
        return y;
    }
    Node* findInternal(Node* root, Type& value) {
        Node* t = lowerBound(value);
        return (t == nullptr || com(value, t->data)) ? nullptr : t;
    }
    Node* upperBound(Type& value) {
        Node *t = root, *r = nullptr;
        while (t != nullptr) {
            if (com(value, t->data))
                r = t, t = t->left;
            else
                t = t->right;
        }
        return r;
    }
    Node* lowerBound(Type& value) {
        Node *t = root, *r = nullptr;
        while (t != nullptr) {
            if (!com(t->data, value))
                r = t, t = t->left;
            else
                t = t->right;
        }
        return r;
    }
    void destroy(Node* root) {
        if (root == nullptr)
            return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
    void inOrderInternal(Node* root) {
        if (root != nullptr) {
            inOrderInternal(root->left);
            cout << root->data << endl;
            inOrderInternal(root->right);
        }
    }
    void postOrderInternal(Node* root) {
        if (root != nullptr) {
            postOrderInternal(root->right);
            cout << root->data << endl;
            postOrderInternal(root->left);
        }
    }
    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
    void printTreeHelper(Node* root, int space) {
        int i;
        if (root != nullptr) {
            space = space + 10;
            printTreeHelper(root->right, space);
            cout << endl;
            for (i = 10; i < space; i++) {
                cout << " ";
            }
            cout << root->data << endl;
            printTreeHelper(root->left, space);
        }
    }
    int MAX(int a, int b) { return (a > b) ? a : b; }
    static Node* getNext(Node* root, Node* next) {
        if (root->right != nullptr) {
            return getMinOf(root->right);
        } else if (root == root->parent->right) {
            while (root->parent != nullptr && root == root->parent->right)
                root = root->parent;
            return root->parent;
        }
        return root->parent;
    }

   public:
    AVLTree() {
        cout << "\nConstructor\n";
        root = nullptr;
        _size = 0;
    }
    ~AVLTree() {
        cout << "\nDestructor\n";
        destroy(root);
    }
    void insert(Type newData) {
        if (root == nullptr) {
            root = new Node(newData);
        } else {
            root = insertInternal(root, newData);
        }
        ++_size;
    }
    iterator find(Type data) {
        return iterator(findInternal(root, data));
    }
    void clear() {
        destroy(root);
        root = nullptr;
        _size = 0;
    }
    void erase(Type data) {
        root = deleteNode(root, data);
    }
    iterator lower_bound(Type data) {
        return iterator(lowerBound(data));
    }
    iterator upper_bound(Type data) {
        return iterator(upperBound(data));
    }
    iterator begin() {
        return iterator(getMinOf(root));
    }
    iterator end() {
        return iterator(nullptr);
    }
    void preOrder() {
    }
    void inOrder() {
        inOrderInternal(root);
    }
    void postOrder() {
        postOrderInternal(root);
    }
    void printTree() {
        printTreeHelper(root, 0);
    }
    unsigned long long size() { return _size; }
};

/*void test1() {
    AVLTree t;
    Type x{0};
    Type* y = t.find(x);
    for (int i = 0; i < 16; i++) {
        t.insert({rand() % 51});
    }
    t.postOrder();
    y = t.lower(x);
    if (y != NULL)
        cout << y << endl;
}*/

int main() {
    // test1();
    AVLTree tt;

    for (int i = 1; i < 16; i++) {
        tt.insert({i});
    }
    // tt.erase({4});
    tt.erase({8});
    // tt.erase({31});
    // tt.erase({5});
    // tt.erase({18});
    tt.printTree();

    //tt.clear();

    auto it = tt.begin();
    if (it != tt.end())
        cout << it->data << endl;

    it = tt.lower_bound({8});
    if (it != tt.end())
        cout << it->data << endl;
    // Type a = *it;

    /*int i = 0;
    for (auto it = tt.begin() ; it!= tt.end(); ++it) {
        cout << it->data << " ";
    }*/
    return 0;
}
