#include <iostream>

using namespace std;

int arr[9][9] = { 0 };
int visit[9] = { 0 };
int numStep = 0;

struct Stack{
    int top;
    int* stack;
    int* point;
    Stack() {
        top = -1;
        stack = new int[100];
    }
    Stack(int size) {
        top = -1;
        stack = new int[size];
    }
    void push(int x) {
        stack[++top] = x;
    }
    void push(int* a, int size) {
        while (size--) {
            this->push(*a++);
        }
    }
    int pop() {
        return stack[--top];
    }
    bool isEmpty() {
        return (top == -1);
    }
    void print() {
        int sum = 0;
        for (int i = 0; i <= top; i++) {
            cout << stack[i] << ", ";
            sum += stack[i];
        }
        cout << "sum=" << sum;
        cout << endl;
    }
};

void DFS(Stack A, int thisStep) {
    numStep++;
    visit[thisStep] = 1;
    bool next = false;
    for (int nextStep = 0; nextStep <= 8; nextStep++) { //Find next point
        if (arr[thisStep][nextStep] == 1) {               //Check next point
            A.push(nextStep);
            DFS(A, nextStep);
            next = true;
            A.pop();
        }
    }
    if (!next) {
        A.print();
    }
}

int main() {
    arr[1][2] = 1;
    arr[1][3] = 1;
    arr[2][4] = 1;
    arr[2][5] = 1;
    arr[4][6] = 1;
    arr[5][8] = 1;
    arr[3][7] = 1;
    arr[3][5] = 1;
    arr[7][8] = 1;
    arr[5][4] = 1;
    Stack A[2];
    A[0].push(1);
    DFS(A[0], 1);
    cout << numStep;
    return 0;
}
