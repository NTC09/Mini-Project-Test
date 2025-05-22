#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    Node* base;
    int value;
	bool operator<(const Node& n) const {
		return value < n.value;
	}
};

priority_queue<Node> pq;
Node nodes[10];

int queue_pop() {
    Node ret = pq.top();
	while (ret.value != ret.base->value) {
		pq.pop();
		ret = pq.top();
	}
	pq.pop();
    return ret.value;
}

int main() {
	for (int i = 0; i < 10; ++i) {
		nodes[i].base = &nodes[i];
		nodes[i].value = i * 10 + 10;
		pq.push(nodes[i]);
	}
	// 
	nodes[2].value = 66;
	pq.push(nodes[2]);

	nodes[5].value = 99;
	pq.push(nodes[5]);

	for (int i = 0; i < 10; ++i) {
		cout << queue_pop() << " ";
	}
	return 0;
}