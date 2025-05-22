
#include <iostream>
#include <set>
#include <avl_iter_2.hpp>

using namespace std;


struct Employee {
    int id, start, end;
    Employee* next;
    bool operator<(const Employee& e) const {
        if (this->start != e.start)
            return this->start < e.start;
        return this->id < e.id;
    }
    friend ostream& operator<<(ostream &ou, Employee& e) {
        ou << e.start;
        return ou;
    }
};

int main() {
    AVLTree<Employee> tt;
    for (int i = 1; i < 16; i++) {
        tt.insert({rand() % 50, i,rand()});
    }
    tt.printTree();

    for (auto it: tt) {
        cout << it.start << " ";
    }
    AVLTree<Employee>::iterator it = tt.begin();

    return 0;
}
