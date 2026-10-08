
// #include <bits/stdc++.h>
// using namespace std;

// struct Node {
//     int data;
//     Node* left;
//     Node* right;

//     Node(int value) {
//         data = value;
//         left = nullptr;
//         right = nullptr;
//     }
// };

// Node* buildTree(vector<int>& arr) {
//     if (arr.empty() || arr[0] == -1) {
//         return nullptr;
//     }

//     Node* root = new Node(arr[0]);
//     queue<Node*> q;
//     q.push(root);

//     int i = 1;

//     while (!q.empty() && i < arr.size()) {
//         Node* current = q.front();
//         q.pop();

//         // Agli value current node ka left child hai
//         if (arr[i] != -1) {
//             current->left = new Node(arr[i]);
//             q.push(current->left);
//         }
//         i++;

//         // Uske baad wali value right child hai
//         if (i < arr.size() && arr[i] != -1) {
//             current->right = new Node(arr[i]);
//             q.push(current->right);
//         }
//         i++;
//     }

//     return root;
// }



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
    // string line;
    // getline(cin, line);

    // stringstream ss(line);
    int n;
    cout<<"Enter Input : "<<endl;
    while (cin>> n) {
        arr.push_back(n);
    }

    Node* root = createTree(arr, 0);

    cout << "Inorder: ";
    inorder(root);

    return 0;
}