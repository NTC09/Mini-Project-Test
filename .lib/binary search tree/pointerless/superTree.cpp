#include <chrono>
#include <iostream>
#include <set>

using namespace std;
using namespace std::chrono;

#define MAX_ 100000

struct myStruct {
    int value;
    /*For tree*/
    int parent;
    int left;
    int right;
    /*For tree*/
    myStruct() {
        left = -1;
        right = -1;
        parent = -1;
        value = -1;
    }
    myStruct(int newValue) {
        left = -1;
        right = -1;
        parent = -1;
        value = newValue;
    }
    void init(int newValue) {
        left = -1;
        right = -1;
        parent = -1;
        value = newValue;
    }
    bool operator<(myStruct& str) const {
        return this->value < str.value;
    }
} Data[MAX_];

struct superTree {
    int root;
    int size;
    int cur, next;
    void reset() {
        root = -1;
        size = 0;
    }
    void add(int id) {
        size++;
        if (root == -1) {
            root = id;
            return;
        }
        register int cur = root;
        register int parent, isLeft;
        while (cur != -1) {
            parent = cur;
            if (Data[id].value < Data[cur].value)
                cur = Data[cur].left, isLeft = 1;
            else
                cur = Data[cur].right, isLeft = 0;
        }
        if (isLeft == 1)
            Data[parent].left = id;
        else
            Data[parent].right = id;
        Data[id].parent = parent;
    }
    int getBigest(int id) {
        int cur = id;
        while (Data[cur].right != -1)
            cur = Data[cur].right;
        return cur;
    }
    int getSmallest(int id) {
        int cur = id;
        while (Data[cur].left != -1)
            cur = Data[cur].left;
        return cur;
    }
    int higher_bound(int value) {
        int id = -1, cur = root;
        while (cur != -1 && cur < size) {
            if (value <= Data[cur].value) {
                id = cur;
                cur = Data[cur].left;
            } else
                cur = Data[cur].right;
        }
        return id;
    }
    int higher(int value) {
        int id = higher_bound(value);
        if (id != -1 && id < size)
            return Data[id].value;
        return -1;
    }
    int lower_bound(int value) {
        int id = -1, cur = root;
        while (cur != -1 && cur < size) {
            if (value > Data[cur].value) {
                id = cur;
                cur = Data[cur].right;
            } else
                cur = Data[cur].left;
        }
        return id;
    }
    int lower(int value) {
        int id = lower_bound(value);
        if (id != -1 && id < size)
            return Data[id].value;
        return -1;
    }
    int search(int value) {
        int cur = root;
        while (Data[cur].value != value) {
            if (value < Data[cur].value)
                cur = Data[cur].left;
            else
                cur = Data[cur].right;
            if (cur == -1)
                break;
        }
        return cur;
    }
    void printSmallToBig() {
        _printSmallToBig(root);
    }
    void _printSmallToBig(int id) {
        if (id != -1) {
            _printSmallToBig(Data[id].left);
            cout << Data[id].value << endl;
            _printSmallToBig(Data[id].right);
        }
    }
    void printBigToSmall() {
        _printBigToSmall(root);
    }
    void _printBigToSmall(int id) {
        if (id != -1) {
            _printBigToSmall(Data[id].right);
            cout << Data[id].value << endl;
            _printBigToSmall(Data[id].left);
        }
    }
    void inOrder(int id) {
        if (id != -1) {
            inOrder(Data[id].left);
            cur = next;
            next = Data[id].value;
            ;
            cout << cur << " " << next << endl;
            inOrder(Data[id].right);
        }
    }
    void deleteNode(int id) {
        int newid = -1;
        size--;
        cout << "Deleting " << Data[id].value << "!" << endl;
        if (Data[id].right != -1) {
            newid = getSmallest(Data[id].right);
        } else if (Data[id].left != -1) {
            newid = getBigest(Data[id].left);
        }
        if (newid != -1) {
            cout << "New : " << Data[newid].value << endl;
            deleteNode(newid);
            Data[newid].left = Data[id].left;
            Data[newid].right = Data[id].right;
            Data[newid].parent = Data[id].parent;
            if (Data[id].left != -1)
                Data[Data[id].left].parent = newid;
            if (Data[id].right != -1)
                Data[Data[id].right].parent = newid;
            cout << Data[id].value << " replaced by " << Data[newid].value << "!" << endl;
            size++;
            // printSmallToBig(0);
        }
        if (id != root) {
            if (Data[id].value < Data[Data[id].parent].value)
                Data[Data[id].parent].left = newid;
            else
                Data[Data[id].parent].right = newid;
        } else {
            root = newid;
            cout << "root = " << Data[root].value << endl;
        }
        cout << "Removed " << Data[id].value << "!" << endl;
    }
    void deleteValue(int value) {
        int id = search(value);
        if (id != -1)
            deleteNode(id);
    }
} Tree;

int _index = 0;
void addValue(int value) {
    Data[_index].init(value);
    Tree.add(_index++);
}

void test() {
    Tree.reset();
    int n = 16;
    for (int i = 0; i < n; i++)
        addValue(rand() % 100);
    Tree.deleteNode(4);
    cout << "Deleted " << Data[4].value << endl;
    Tree._printSmallToBig(0);
}

int main() {
    test();
    return 1;
    Tree.reset();
    set<int> Set;
    Set.insert(12);
    // uto en = high_resolution_clock::now(), st = en;
    Set.find(12);
    int id = Tree.lower_bound(1);
    cout << id << " ";
    if (id != -1)
        cout << Data[id].value;
    cout << endl;
    addValue(8);
    addValue(4);
    addValue(12);
    addValue(2);
    addValue(6);
    addValue(10);
    addValue(14);
    addValue(1);
    addValue(3);
    addValue(5);
    addValue(7);
    addValue(9);
    addValue(11);
    addValue(13);
    addValue(15);
    id = Tree.higher_bound(10);
    cout << id << " ";
    if (id != -1)
        cout << Data[id].value;
    cout << endl;
    cout << endl;
    Tree.deleteValue(14);
    // en = high_resolution_clock::now();
    // double T = duration_cast<microseconds>(en - st).count();
    // cout << T / 1e6;

    Tree.printSmallToBig();
    return 0;
}