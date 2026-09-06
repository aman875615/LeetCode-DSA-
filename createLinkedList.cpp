#include<iostream>
using namespace std;

class Node{

    public:
    int data ;
    Node* next;
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};
Node* createNode(int data){
        Node* newNode = new Node(data);
        newNode->next = NULL;
        return newNode;
       
}
void InsertAtHead(Node* &head,int data){
    Node* node1 =  createNode(data);
    node1->next = head;
    head = node1;
}
void printNode(Node* head ){
    Node* temp = head ;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}


void insertAtPosition(Node* head ,int k,int data){
    Node* temp = head;
    for(int i=0;i<k-2;i++){
        temp = temp->next;
    }
    Node * node = createNode(data);
    node->next = temp->next;
    temp->next = node;
}

int main(){
    int val=10;
    Node* newNode = new Node(val);
    cout<<newNode->data<<endl;

    Node* node1 = createNode(15);

    cout<<node1->data<<endl;
    cout<<node1->next<<endl;
    Node* head = NULL;
    // insert  at head 


     InsertAtHead(head,20);
     cout<<head->data<<endl;
     InsertAtHead(head,30);
     cout<<head->data<<endl;
     InsertAtHead(head,40);
     cout<<head->data<<endl;

    printNode(head);
    cout<<endl;
     insertAtPosition(head,1,55);
     printNode(head);

    return 0;
}

