#include <iostream>
using namespace std;

struct Queue {
    int data[10];
    int front;
    int rear;
    Queue() {
        front = 0;
        rear = -1;
    }
    void init() {
        front = 0;
        rear = -1;
    }
    void enque(int next) {
        data[++rear] = next;
        if (rear == 9) {
            register int i = 0;
            while (!this->isempty()) {
                data[i++] = this->deque();
            }
            front = 0;
            rear = i-1;
        }
    }
    int& deque() {
        return data[front++];
    }
    bool isempty() {
        return rear < front;
    }
} Q;

int main(){
    for (int i=0;i<9;i++){
        Q.enque(i);
    }
    cout << Q.deque() << endl;
    cout << Q.deque() << endl;
    cout << Q.deque() << endl;
    cout << Q.deque() << endl;
    for (int i=9;i<12;i++){
        Q.enque(i);
    }
    while (!Q.isempty()){
        cout << Q.deque() << endl;
    }
    return 0;
}