#include <iostream>
#include <set>

using namespace std;

#define fn void

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

template <typename Type>
struct smaller {
    bool operator()(const Type& t1, const Type& t2) {
        return t1 < t2;
    }
};

//typedef smaller compare;
template<typename Type, typename compare = smaller<Type>>
class RedBlackTree {
   private:
    static const bool black = true;
    static const bool red = false;
    class Node {
       public:
        Node* left;
        Node* right;
        Node* parent;
        bool color;  // black: true; red: false
        Type data;
        // method
        Node() {
            left = right = parent = nullptr;
            color = black;
        }
        Node(Type data, bool color) {
            left = right = parent = nullptr;
            this->color = color;
            this->data = data;
        }
    };
    Node* root;
    compare com;

    Node* insertInternal(Node* root, Type& data) {
        bool redConflict = false;
        if (root == nullptr) {
            return new Node(data, red);
        } else {
            if (com(data, root->data)) {
                root->left = insertInternal(root->left, data);
                root->left->parent = root;
                if (root != this->root) {
                    if (root->color == red && root->left->color == red)
                        redConflict = true;
                }
            } else {
                root->right = insertInternal(root->right, data);
                root->right->parent = root;
                if (root != this->root) {
                    if (root->color == red && root->right->color == red)
                        redConflict = true;
                }
            }
        }
        root = balance(root);
        if (redConflict) {
            resolve(root);
            redConflict = false;
        }
        return root;
    }

    bool leftLeft;
    bool leftRight;
    bool rightRight;
    bool rightLeft;
    void resolve(Node* root) {
        if (root->parent->right == root) {
            if (root->parent->left == nullptr || root->parent->left->color == black) {
                if (root->left != nullptr && root->left->color == red)
                    rightLeft = true;
                else if (root->right != nullptr && root->right->color == red)
                    leftLeft = true;
            } else {
                root->parent->left->color = black;
                root->color = black;
                if (root->parent != this->root)
                    root->parent->color = red;
            }
        } else {
            if (root->parent->right == nullptr || root->parent->right->color == black) {
                if (root->left != nullptr && root->left->color == red)
                    rightRight = true;
                else if (root->right != nullptr && root->right->color == red)
                    leftRight = true;
            } else {
                root->parent->right->color = black;
                root->color = black;
                if (root->parent != this->root)
                    root->parent->color == red;
            }
        }
    }

    Node* balance(Node* root) {
        if (leftLeft) {
            leftLeft = false;
            root = leftRotate(root);
            root->color = black;
            root->left->color = red;
        } else if (rightRight) {
            rightRight = false;
            root = rightRotate(root);
            root->color = black;
            root->right->color = red;
        } else if (rightLeft) {
            rightLeft = false;
            root->right = rightRotate(root->right);
            root->right->parent = root;
            root = leftRotate(root);
            root->color = black;
            root->right->color = red;
        } else if (leftRight) {
            leftRight = false;
            root->left = leftRotate(root->left);
            root->left->parent = root;
            root = rightRotate(root);
            root->color = black;
            root->right->color = red;
        }
        return root;
    }

    Type* findInternal(Node* root, Type& value) {
        Type* t = lowerBound(value);
        return (t == nullptr || com(value, *t)) ? nullptr : t;
    }
    Type* upperBound(Type& value) {
        Node *t = root, *r;
        while (t != nullptr) {
            if (com(value, t->data))
                r = t, t = t->left;
            else
                t = t->right;
        }
        return (r == nullptr) ? nullptr : &r->data;
    }
    Type* lowerBound(Type& value) {
        Node *t = root, *r;
        while (t != nullptr) {
            if (com(t->data, value))
                t = t->right;
            else
                r = t, t = t->left;
        }
        return (r == nullptr) ? nullptr : &r->data;
    }
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->parent = x;
        if (T2 != nullptr)
            T2->parent = y;
        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->parent = y;
        if (T2 != nullptr)
            T2->parent = x;
        return y;
    }
    void destroy(Node* root) {
        if (root == nullptr)
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
        if (root != nullptr) {
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
        if (root != nullptr) {
            postOrderInternal(root->right);
            cout << root->data << endl;
            postOrderInternal(root->left);
        }
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

   public:
    RedBlackTree() {
        cout << "Constructor\n";
        root = nullptr;
        leftLeft = leftRight = rightLeft = rightRight = false;
    }
    ~RedBlackTree() {
        cout << "Destructor\n";
        destroy(root);
    }
    void insert(Type data) {
        if (root == nullptr) {
            root = new Node(data, black);
        } else {
            root = insertInternal(root, data);
            if (root->color == red)
                root->color = black;
        }
    }
    /**
     * @brief Find data in tree
     *
     * @param data The data need to find
     * @return Type* Pointer to the data in tree.
     * @return nullptr if not found
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
     * @return nullptr if not found
     */
    Type* lower(Type data) {
        Type* t = lowerBound(data);
        return (t == nullptr) ? nullptr : ((com(*t, data)) ? nullptr : t);
    }
    /**
     * @brief Find data in tree that bigger than data given
     *
     * @param data The data need to find
     * @return Type* Pointer to the data in tree.
     * @return nullptr if not found
     */
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
};

fn test1() {
    RedBlackTree<Type> t;
    Type x{22};
    Type* y = t.find(x);
    for (int i = 1; i < 18; i++) {
        t.insert({rand() % 67});
    }
    t.printTree();
    y = t.upper(x);
    if (y != nullptr) {
        cout << *y << endl;
        cout << y << endl;
    }
}

int main() {
    test1();
    return 0;
}