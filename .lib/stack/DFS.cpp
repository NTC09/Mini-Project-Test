#include <iostream>

using namespace std;

int a[9][9] = {0};

struct Stack{
    int top;
    int *stack;
    int *point;
    Stack(){
        top=-1;
        stack = new int [100];
    }
    Stack(int size){
        top = -1;
        stack = new int [size];
    }
    void push(int x){
        stack[++top] = x;
    }
    void push(int *a,int size){
        while(size--){
            this->push(*a++);
        }
    }
    int pop(){
        return stack[--top];
    }
    bool isEmpty(){
        return (top == -1);
    }
};

void DFS(Stack A,int v){
    A.push(5);
    while(A.isEmpty()){

    }
}

int main(){
    a[5][7] = 1;
    a[5][6] = 1;
    a[7][1] = 1;
    a[6][4] = 1;
    a[6][2] = 1;
    a[6][8] = 1;
    a[4][3] = 1;
    a[4][7] = 1;
    a[2][3] = 1;
    Stack A;
    DFS(A,5);
    return 0;
}
