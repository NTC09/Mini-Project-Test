#include <chrono>
#include <iostream>
#include <set>

using namespace std;
using namespace std::chrono;

#define MAX 1000000

class Type {
   public:
   int value;
    bool operator<(Type& str) const {
        return this->value < str.value;
    }
    bool operator>(Type& str) const {
        return this->value > str.value;
    }
    bool operator<=(Type& str) const {
        return this->value <= str.value;
    }
    bool operator!=(Type& str) const {
        return this->value != str.value;
    }
} types[1000000];

template<typename Type>
class superTree {
#define null 0
   private:
    class Node {
       public:
        Type* value;
        int parent;
        int left;
        int right;
    }* nodes;
    int nodeNumber;
    int root;
    int size;
    // private methods
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
            if (*nodes[id].value < *nodes[cur].value)
                cur = nodes[cur].left, isLeft = 1;
            else
                cur = nodes[cur].right, isLeft = 0;
        }
        if (isLeft == 1)
            nodes[parent].left = id;
        else
            nodes[parent].right = id;
        nodes[id].parent = parent;
    }
    int search(Type value) {
        int cur = root;
        while (*nodes[cur].value != value) {
            if (value < *nodes[cur].value)
                cur = nodes[cur].left;
            else
                cur = nodes[cur].right;
            if (cur == -1)
                break;
        }
        return cur;
    }
    int lower_bound(Type value) {
        int id = -1, cur = root;
        while (cur != -1 && cur < size) {
            if (value > *nodes[cur].value) {
                id = cur;
                cur = nodes[cur].right;
            } else
                cur = nodes[cur].left;
        }
        return id;
    }
    int higher_bound(Type value) {
        int id = -1, cur = root;
        while (cur != -1 && cur < size) {
            if (value <= *nodes[cur].value) {
                id = cur;
                cur = nodes[cur].left;
            } else
                cur = nodes[cur].right;
        }
        return id;
    }
    void deleteNode(int id) {
        int newid = -1;
        size--;
        cout << "Deleting " << nodes[id].value << "!" << endl;
        if (nodes[id].right != -1) {
            newid = getSmallest(nodes[id].right);
        } else if (nodes[id].left != -1) {
            newid = getBigest(nodes[id].left);
        }
        if (newid != -1) {
            cout << "New : " << nodes[newid].value << endl;
            deleteNode(newid);
            nodes[newid].left = nodes[id].left;
            nodes[newid].right = nodes[id].right;
            nodes[newid].parent = nodes[id].parent;
            if (nodes[id].left != -1)
                nodes[nodes[id].left].parent = newid;
            if (nodes[id].right != -1)
                nodes[nodes[id].right].parent = newid;
            cout << nodes[id].value << " replaced by " << nodes[newid].value << "!" << endl;
            size++;
            // printSmallToBig(0);
        }
        if (id != root) {
            if (*nodes[id].value < *nodes[nodes[id].parent].value)
                nodes[nodes[id].parent].left = newid;
            else
                nodes[nodes[id].parent].right = newid;
        } else {
            root = newid;
            cout << "root = " << nodes[root].value << endl;
        }
        cout << "Removed " << nodes[id].value << "!" << endl;
    }

   public:
    void init(int size) {
        nodes = new Node[size];
        root = -1;
        nodeNumber = 0;
        this->size = 0;
    }
    void init() {
        root = -1;
        nodeNumber = 0;
        this->size = 0;
    }
    void reset() {
        root = -1;
        size = 0;
    }
    void insert(Type* type) {
        nodes[nodeNumber] = {type,-1,-1,-1};
        add(nodeNumber++);
    }
    
    int getBigest(int id) {
        int cur = id;
        while (nodes[cur].right != -1)
            cur = nodes[cur].right;
        return cur;
    }
    int getSmallest(int id) {
        int cur = id;
        while (nodes[cur].left != -1)
            cur = nodes[cur].left;
        return cur;
    }
    
    Type* higher(Type value) {
        int id = higher_bound(value);
        if (id != -1 && id < size)
            return nodes[id].value;
        return null;
    }
    
    Type* lower(Type value) {
        int id = lower_bound(value);
        if (id != -1 && id < size)
            return nodes[id].value;
        return null;
    }
    
    void printSmallToBig() {
        _printSmallToBig(root);
    }
    void _printSmallToBig(int id) {
        if (id != -1) {
            _printSmallToBig(nodes[id].left);
            cout << nodes[id].value->value << endl;
            _printSmallToBig(nodes[id].right);
        }
    }
    void printBigToSmall() {
        _printBigToSmall(root);
    }
    void _printBigToSmall(int id) {
        if (id != -1) {
            _printBigToSmall(nodes[id].right);
            cout << nodes[id].value->value << endl;
            _printBigToSmall(nodes[id].left);
        }
    }
    
    void erase(Type value) {
        int id = search(value);
        if (id != -1)
            deleteNode(id);
    }
#undef null
}; 
superTree<Type>Tree;

int _index = 0;

void addValue(int value) {
    types[_index].value = value;
    Tree.insert(&types[_index++]);
}

void test() {
    Tree.reset();
    int n = 16;
    for (int i = 0; i < n; i++)
        addValue(rand() % 100);
    //Tree.deleteNode(4);
    //cout << "Deleted " << nodes[4].value << endl;
    //Tree._printSmallToBig(0);
}

int main() {
    Tree.init(1e6);
    Type* id = Tree.lower({1});
    /*cout << id << " ";
    if (id != 0)
        cout << id->value;
    cout << endl;*/
    for (int  i = 0; i < 1e5; i++)
    {
        addValue(rand());
    }
    return 0;
    /*
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
    addValue(15);*/
    id = Tree.higher({10});
    cout << id << " ";
    if (id != 0)
        cout << id->value;
    cout << endl;
    cout << endl;
    Tree.erase({41});
    Tree.erase({18467});
    // en = high_resolution_clock::now();
    // double T = duration_cast<microseconds>(en - st).count();
    // cout << T / 1e6;

    Tree.printSmallToBig();
    cout << "Done!";
    return 0;
}