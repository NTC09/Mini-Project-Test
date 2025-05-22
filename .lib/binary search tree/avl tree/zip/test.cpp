
#include <iostream>
#include <set>
#include <avl_iter_lite.hpp>

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
        tt.insert({i,i,i});
    }

    for (auto it: tt) {
        cout << it.start << " ";
    }

    auto it = tt.begin();
    it++;
    cout << it->start << " ";

    tt.erase({1,1,1});
    it = tt.find({1,1,1});
    it = tt.find({8,8,8});
    it = tt.lower_bound({2, 2, 2});
    it = tt.upper_bound({2, 2, 2});
    tt.clear();
    return 0;
}
