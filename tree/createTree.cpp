#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

Node* createTree(vector<int>& arr, int i) {

    if (i >= arr.size() || arr[i] == -1)
        return NULL;

    Node* root = new Node(arr[i]);

    root->left = createTree(arr, 2 * i + 1);
    root->right = createTree(arr, 2 * i + 2);

    return root;
}

// Inorder: Left -> Root -> Right
void inorder(Node* root) {

    if (root == NULL)
        return;

    inorder(root->left);

    cout << root->data << " ";

    inorder(root->right);
}

int main() {

    vector<int> arr;
    string line;
    getline(cin, line);

    stringstream ss(line);
    int n;
    cout<<"Enter Input : "<<endl;
    while (ss>> n) {
        arr.push_back(n);
    }

    Node* root = createTree(arr, 0);

    cout << "Inorder: ";
    inorder(root);

    return 0;
}