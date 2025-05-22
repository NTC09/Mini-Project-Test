#include <chrono>
#include <iostream>
using namespace std;
typedef struct Node {
    int data;
    Node* left;
    Node* right;
} node_t;

void Free(node_t* root) {
    if (root == NULL)
        return;

    Free(root->left);
    Free(root->right);
    free(root);
}

int LeftOf(const int value, const node_t* root) {
    // Nếu bạn muốn cây BST cho phép giá trị trùng lặp, hãy sử dụng dòng code thứ 2
    return value < root->data;
    //    return value <= root->data;
}

int RightOf(const int value, const node_t* root) {
    return value > root->data;
}

node_t* Insert(node_t* root, const int value) {
    if (root == NULL) {
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->left = NULL;
        node->right = NULL;
        node->data = value;
        return node;
    }
    if (LeftOf(value, root))
        root->left = Insert(root->left, value);
    else if (RightOf(value, root))
        root->right = Insert(root->right, value);
    return root;
}

bool Search(const node_t* root, int value) {
    if (root == NULL)
        return false;
    if (root->data == value) {
        return true;
    }
    else if (LeftOf(value, root)) {
        return Search(root->left, value);
    }
    else if (RightOf(value, root)) {
        return Search(root->right, value);
    }
}

int LeftMostValue(const node_t* root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

node_t* Delete(node_t* root, int value) {
    if (root == NULL)
        return root;
    if (LeftOf(value, root))
        root->left = Delete(root->left, value);
    else if (RightOf(value, root))
        root->right = Delete(root->right, value);
    else {
        // root->data == value, delete this node
        if (root->left == NULL) {
            node_t* newRoot = root->right;
            free(root);
            return newRoot;
        }
        if (root->right == NULL) {
            node_t* newRoot = root->left;
            free(root);
            return newRoot;
        }
        root->data = LeftMostValue(root->right);
        root->right = Delete(root->right, root->data);
    }
    return root;
}

void PreOrder(node_t* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(node_t* root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->data);
        // return root->data;
        InOrder(root->right);
    }
}

void PostOrder(node_t* root) {
    if (root != NULL) {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    auto st = chrono::high_resolution_clock::now();
    node_t* root = NULL;
    int size = 100, t;
    int* a = (int*)malloc(sizeof(size));
    for (int i = 0; i < size; i++) {
        t = rand();
        root = Insert(root, rand());
    }
    printf("\nDuyet inorder  : ");
    InOrder(root);
    for (int i = 0; i < size; i++)
        root = Delete(root, rand());
    for (int i = 0; i < size; i++)
        root = Insert(root, rand());
    Free(root);
    root = NULL;
    auto en = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::microseconds>(en - st).count();
    cout << endl
        << time / 1.0e6 << endl;
    return 0;
}