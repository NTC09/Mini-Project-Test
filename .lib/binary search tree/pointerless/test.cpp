// #include<set>
// using namespace std;
// set<int>s;

int root;
int newId;

struct Node {
    int value;
    int left, right;
    void init() { left = right = -1; }
} nodes[1000];

#define leftOf(id) nodes[id].left
#define rightOf(id) nodes[id].right
#define valueOf(id) nodes[id].value
#define compare(i1, i2) nodes[i1].value < nodes[i2].value

void init() {
    root = -1;
    newId = -1;
}
void add(int level) {
    ++newId;
    nodes[newId].left = -1;
    nodes[newId].right = -1;
    nodes[newId].value = level;
    if (root == -1) {
        root = newId;
        return;
    }
    register int parent, cur, isleft;
    for (cur = root; cur != -1;) {
        parent = cur;
        if (compare(newId, cur))
            isleft = 1, cur = leftOf(cur);
        else
            isleft = 0, cur = rightOf(cur);
    }
    if (isleft)
        leftOf(parent) = newId;
    else
        rightOf(parent) = newId;
}
int getNextLevel(int currentLevel) {
    register int id, cur;
    for (cur = root, id = -1; cur != -1;) {
        if (currentLevel < valueOf(cur)) {
            cur = leftOf(cur);
        } else {
            id = cur;
            cur = rightOf(cur);
        }
    }
    if (id == -1)
        return -1;
    return valueOf(id);
}
