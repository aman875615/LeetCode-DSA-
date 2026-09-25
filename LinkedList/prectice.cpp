#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        this->next=NULL;
    }
};

int create_node(int data){
    Node* newNode = new Node(data);
    newNode->next = NULL;
    return newNode->data;
}
int main(){
    int n;
    cin>>n;
    cout<< create_node(n);
    

    return 0;
}