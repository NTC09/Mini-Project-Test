#include <iostream>
#include <set>

using namespace std;

template <typename Type>
struct smaller {
    bool operator()(const Type& t1, const Type& t2) {
        return t1 < t2;
    }
};

typedef void (*callable)();

template <typename Type, typename compare = smaller<Type>>
class AVLTree {
   private:
    class Node {
       public:
        Node* left;
        Node* right;
        Node* parent;
        int height;
        Type data;
        // method
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
    Node* root;
    compare com;

    Node* insertInternal(Node* root, Type& newData) {
        if (root == nullptr) {
            return new Node(newData);
        } else {
            if (com(newData, root->data)) {
                root->left = insertInternal(root->left, newData);
                root->left->parent = root;
            }
            else {
                root->right = insertInternal(root->right, newData);
                root->right->parent = root;
            }
        }
        return balancing(root);
    }
    Node* deleteNode(Node* root, Type data) {
        if (root == nullptr)
            return root;
        if (com(data, root->data))
            root->left = deleteNode(root->left, data);
        else if (com(root->data, data))
            root->right = deleteNode(root->right, data);
        else {
            --size;
            // node with only one child or no child
            if ((root->left == nullptr) ||
                (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else              // One child case
                    *root = *temp;  // Copy the contents of
                                    // the non-empty child
                delete temp;
            } else {
                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                Node* temp = getMinOf(root->right);

                // Copy the inorder successor's data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }
        return balancing(root);
    }
    Node* balancing(Node* root) {
        if (root == nullptr)
            return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Left left Case
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);
        // Left Right Case
        if (balance > 1 &&
            getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Right Right Case
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);
        // Right Left Case
        if (balance < -1 &&
            getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    Node* getMinOf(Node* root) {
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
        y->parent = x;
        if(T2 != nullptr) {
            T2->parent = y;
        }

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;
        x->parent = y;
        if (T2 != NULL)
            T2->parent = x;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }
    Type* findInternal(Node* root, Type& value) {
        Type* t = lowerBound(value);
        return (t == nullptr || com(value, *t)) ? nullptr : t;
    }
    Type* upperBound(Type& value) {
        Node *t = root, *r;
        while (t != nullptr) {
            r = t;
            if (com(value, t->data))
                t = t->left;
            else
                t = t->right;
        }
        return (r == nullptr) ? nullptr : &r->data;
    }
    Type* lowerBound(Type& value) {
        Node *t = root, *r;
        while (t != nullptr) {
            r = t;
            if (com(t->data, value))
                t = t->right;
            else if (com(value, t->data))
                t = t->left;
            else
                return &t->data;
        }
        return (r == nullptr) ? nullptr : &r->data;
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
            space = space + 5;
            printTreeHelper(root->right, space);
            cout << endl;
            for (i = 5; i < space; i++) {
                cout << " ";
            }
            cout << root->data << endl;
            printTreeHelper(root->left, space);
        }
    }

    void loopInternal(Node* root) {
        if (root != nullptr) {
            loopInternal(root->left);
            loop();
            loopInternal(root->right);
        }
    }

   public:
    int size;
    AVLTree() {
        cout << "Constructor\n";
        root = nullptr;
        size = 0;
        loop = nullptr;
    }
    ~AVLTree() {
        cout << "Destructor\n";
        destroy(root);
    }
    void insert(Type newData) {
        if (root == nullptr) {
            root = new Node(newData);
        } else {
            root = insertInternal(root, newData);
        }
        ++size;
    }
    Type* find(Type data) {
        return findInternal(root, data);
    }
    void clear() {
        destroy(root);
        root = nullptr;
        size = 0;
    }
    void erase(Type data) {
        root = deleteNode(root, data);
    }
    Type* lower(Type data) {
        Type* t = lowerBound(data);
        return (t == nullptr) ? nullptr : ((com(*t, data)) ? nullptr : t);
    }
    Type* upper(Type data) {
        Type* t = upperBound(data);
        return (t == nullptr) ? nullptr : ((com(data, *t)) ? t : nullptr);
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

    callable loop;
    void loopOver(callable loop) {
        this->loop = loop;
    }
};
