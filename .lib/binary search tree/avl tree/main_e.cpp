#include <iostream>
#include <set>
#include <avl_tree.hpp>

using namespace std;



fn test1() {
    AVLTree t;
    Type x{0};
    Type* y = t.find(x);
    for (int i = 0; i < 20; i++) {
        t.insert({rand() % 51});
    }
    t.printTree();
    y = t.lower(x);
    if (y != NULL)
        cout << *y << endl;
    cout << y << endl;
}

int main() {
    //test1();
    AVLTree tt;
    for (int i = 1; i < 16; i++) {
        tt.insert(i);
    }
    tt.printTree();
    return 0;
}
