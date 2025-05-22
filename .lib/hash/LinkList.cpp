#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(){
        data = NULL;
    }
};

Node* create(int data){
    Node* temp;
    temp = new Node;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

struct linkList{
    Node *head;
    Node *tail;
    linkList(){
        this->head = NULL;
        this->tail = NULL;
    }
    Node* addTail(int data){
        Node *temp;
        temp = new Node;
        temp = create(data);
        tail->next = temp;
        tail = temp;
        return temp;
    }
    Node* addHead(int data){
        Node *temp;
        temp = new Node;
        temp = create(data);
        temp->next = head;
        head = temp;
        return temp;
    }
};



int main(){
    unordered_map<string, int> Map;
    Map["abc"] = 1;
    Map.find("abc");
    cout << endl;

    return 0;
}