#include <iostream>
#include <set>

using namespace std;

#define fn void

#ifndef NULL
#define NULL 0LL
#endif

class Type {
   public:
    int data;
    /*Type() {
        data = 0;
    }*/
    bool operator<(const Type& type) const {
        return this->data < type.data;
    }
    friend ostream& operator<<(ostream& ou, Type& t) {
        ou << t.data;
        return ou;
    }
};

// template <typename Type>
struct smaller {
    bool operator()(const Type& t1, const Type& t2) {
        return t1 < t2;
    }
};

typedef smaller compare;
// template<typename Type, typename compare = smaller<Type>>
class AVLTree {
   private:
    class Node {
       public:
        Node* left;
        Node* right;
        int height;  // black: true; red: false
        Type data;
        // method
        Node() {
            left = right = NULL;
            height = 1;
        }
        Node(Type newData) {
            left = right = NULL;
            data = newData;
        }
    };
    Node* root;
    compare com;

    Node* insertInternal(Node* root, Type& newData) {
        if (root == NULL) {
            return new Node(newData);
        } else {
            if (com(newData, root->data)) 
                root->left = insertInternal(root->left, newData);
            else 
                root->right = insertInternal(root->right, newData);
        }
        balancing(root);
        return root;
    }

    Node* deleteNode(Node* root, Type data) {
        if (root == NULL)
            return root;
        if (com(data, root->data))
            root->left = deleteNode(root->left, data);
        else if (com(root->data, data))
            root->right = deleteNode(root->right, data);
        else {
            // node with only one child or no child
            if ((root->left == NULL) ||
                (root->right == NULL)) {
                Node* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else              // One child case
                    *root = *temp;  // Copy the contents of
                                    // the non-empty child
                free(temp);
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
        balancing(root);
    }

    Node* balancing(Node* root) {
        if (root == NULL)
            return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

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

    Node *getMinOf(Node *root) {
        if (root == NULL || root->left == NULL)
            return root;
        return getMinOf(root->left);
    }

    int getBalance(Node* N) {
        if (N == NULL)
            return 0;
        return height(N->left) -
               height(N->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Type* findInternal(Node* root, Type& value) {
        Type* t = lowerBound(value);
        return (t == NULL || com(value, *t)) ? NULL : t;
    }
    Type* upperBound(Type& value) {
        Node *t = root, *r;
        while (t != NULL) {
            r = t;
            if (com(value, t->data))
                t = t->left;
            else
                t = t->right;
        }
        return (r == NULL) ? NULL : &r->data;
    }
    Type* lowerBound(Type& value) {
        Node *t = root, *r;
        while (t != NULL) {
            r = t;
            if (com(t->data, value))
                t = t->right;
            else if (com(value, t->data))
                t = t->left;
            else
                return &t->data;
        }
        return (r == NULL) ? NULL : &r->data;
    }

    void destroy(Node* root) {
        if (root == NULL)
            return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
    /**
     * @brief Access from smallest to biggest Node
     *
     * @param root pointer of a Node
     */
    void inOrderInternal(Node* root) {
        if (root != NULL) {
            inOrderInternal(root->left);
            cout << root->data << endl;
            inOrderInternal(root->right);
        }
    }
    /**
     * @brief Access from biggest to smallest Node
     *
     * @param root pointer of a Node
     */
    void postOrderInternal(Node* root) {
        if (root != NULL) {
            postOrderInternal(root->right);
            cout << root->data << endl;
            postOrderInternal(root->left);
        }
    }
    int height(Node* N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

   public:
    AVLTree() {
        cout << "Constructor\n";
        root = NULL;
    }
    ~AVLTree() {
        cout << "Destructor\n";
        destroy(root);
    }
    void insert(Type newData) {
        if (root == NULL) {
            root = new Node(newData);
        } else {
            root = insertInternal(root, newData);
        }
    }
    /**
     * @brief Find data in tree
     *
     * @param data The data need to find
     * @return Type* Pointer to the data in tree.
     * @return NULL if not found
     */
    Type* find(Type data) {
        return findInternal(root, data);
    }
    void clear() {
        destroy(root);
    }
    void erase(Type data) {
    }
    /**
     * @brief Find data in tree that bigger or equal to data given
     *
     * @param data The data need to find
     * @return Type* Pointer to the data in tree.
     * @return NULL if not found
     */
    Type* lower(Type data) {
        Type* t = lowerBound(data);
        return (t == NULL) ? NULL : ((com(*t, data)) ? NULL : t);
    }
    /**
     * @brief Find data in tree that bigger than data given
     *
     * @param data The data need to find
     * @return Type* Pointer to the data in tree.
     * @return NULL if not found
     */
    Type* upper(Type data) {
        Type* t = upperBound(data);
        return (t == NULL) ? NULL : ((com(data, *t)) ? t : NULL);
    }
    void preOrder() {
    }
    void inOrder() {
        inOrderInternal(root);
    }
    void postOrder() {
        postOrderInternal(root);
    }
};

fn test1() {
    AVLTree t;
    Type x{0};
    Type* y = t.find(x);
    for (int i = 0; i < 20; i++) {
        t.insert({rand() % 51});
    }
    t.postOrder();
    y = t.lower(x);
    if (y != NULL)
        cout << *y << endl;
    cout << y << endl;
}

int main() {
    test1();
    return 0;
}
