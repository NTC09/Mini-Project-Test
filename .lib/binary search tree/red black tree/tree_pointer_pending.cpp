#include <iostream>
#include <set>

using namespace std;

#ifndef NULL
#define NULL 0LL
#endif

class Type {
   public:
    long long data;
    Type() {
        data = 0;
    }
    Type(long long data) {
        this->data = data;
    }
    bool operator<(const Type& type) const {
        return this->data < type.data;
    }
    bool operator==(const Type& type) const {
        return this->data == type.data;
    }
};

template<typename Type>
class BinaryTree {
#define black true
#define red false
   private:
    class Node {
       public:
        Node* left;
        Node* right;
        Node* parent;
        bool color;  // black: true; red: false
        Type data;
        // method
        Node() {
            left = right = parent = NULL;
            color = black;
        }
        Node(Type newData, bool color) {
            left = right = parent = NULL;
            this->color = color;
            data = newData;
        }
    };
    Node* root;
    Node* insertInternal(Node* root, Type newData) {
        if (root == NULL) {
            return new Node(newData, red);
        } else {
            if (newData < root->data) {
                root->left = insertInternal(root->left, newData);
                root->left->parent = root;
            } else {
                root->right = insertInternal(root->right, newData);
                root->right->parent = root;
            }
        }
        return root;
    }
    Node* findInternal(Node* root, Type data) {
        if (root == NULL)
            return NULL;
        if (root->data == data)
            return root;
        else if (data < root->data)
            return findInternal(root->left, data);
        else
            return findInternal(root->right, data);
    }
    Node* eraseInternal(Node* root, Type data) {
        if (root == NULL)
            return root;
        if (data == root->data) {
            if (root->left == NULL) {
                Node* newRoot = root->right;
                delete root;
                return newRoot;
            }
            if (root->right == NULL) {
                Node* newRoot = root->left;
                delete root;
                return newRoot;
            }
            root->data = getMinOf(root->right);
            root->right = eraseInternal(root->right, root->data);
        } else if (data < root->data) {
            root->left = eraseInternal(root->left, data);
        } else {
            root->right = eraseInternal(root->right, data);
        }
        return root;
    }
    Type getMinOf(Node *root) {
        while (root->left != NULL)
            root = root->left;
        return root->data;
    }
    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            cout << node->data << endl;
            inOrder(node->right);
        }
    }

   public:
    BinaryTree() {
        root = NULL;
    }
    void insert(Type newData) {
        if (root == NULL) {
            root = new Node(newData, black);
        } else {
            root = insertInternal(root, newData);
            if (root->color == red)
                root->color = black;
        }
    }
    Type find(Type data) {
        Node* node = findInternal(root, data);
        if (node == NULL)
            return Type();
        return node->data;
    }
    void erase(Type data) {
        Node* node = findInternal(root, data);
        if (node != NULL)
            root = eraseInternal(root, data);
    }
    void inOrder() {
        inOrder(root);
    }
};

int main() {
    BinaryTree<int> t;
    for (int i = 0; i < 1e5; i++)
        t.insert(rand());
    //t.erase(41);a
    //t.inOrder();
    return 0;
}