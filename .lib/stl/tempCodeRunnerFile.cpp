#include <list>
#include <iostream>

using namespace std;

struct Node {
    list<Node*>::iterator it;
    int val;
};


list<Node*> L;
Node nodes[10];

int main() {
    for (int i = 0; i < 10; ++i) {
		nodes[i].val = i;
		nodes[i].it = L.insert(L.end(), &nodes[i]);
        //L.push_front();
		//nodes[i].it = L.begin();
    }

    for (auto i : L)
        cout << i->val << " " << (*i->it)->val << endl;
 