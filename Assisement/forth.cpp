
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

Node* insert(Node* root, int value) {
    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

Node* insert(const vector<int>& values) {
    Node* root = NULL;
    for (int value : values)
        root = insert(root, value);
    return root;
}


void inorder(Node* root) {

    if (root == NULL)
        return;

    inorder(root->left);

    cout << root->data << " ";

    inorder(root->right);
}

vector<int> topView(Node* root) {
    vector<int> view;
    if (root == NULL)
        return view;

    map<int, int> topNodes;
    queue<pair<Node*, int>> nodes;
    nodes.push({root, 0});

    while (!nodes.empty()) {
        auto [node, distance] = nodes.front();
        nodes.pop();

        if (topNodes.find(distance) == topNodes.end())
            topNodes[distance] = node->data;

        if (node->left != NULL)
            nodes.push({node->left, distance - 1});
        if (node->right != NULL)
            nodes.push({node->right, distance + 1});
    }

    for (const auto& [distance, value] : topNodes)
        view.push_back(value);

    return view;
}

void leftView(Node* root, vector<int>& view, int level) {
    if (root == NULL)
        return;

    if (level == view.size())
        view.push_back(root->data);

    leftView(root->left, view, level + 1);
    leftView(root->right, view, level + 1);
}

void rightView(Node* root, vector<int>& view, int level) {
    if (root == NULL)
        return;

    if (level == view.size())
        view.push_back(root->data);

    rightView(root->right, view, level + 1);
    rightView(root->left, view, level + 1);
}

vector<int> bottomView(Node* root) {
    vector<int> view;
    if (root == NULL)
        return view;

    map<int, int> mp;
    queue<pair<Node*, int>> nodes;
    nodes.push({root, 0});

    while (!nodes.empty()) {
        auto [node, distance] = nodes.front();
        nodes.pop();
        mp[distance] = node->data;

        if (node->left != NULL)
            nodes.push({node->left, distance - 1});
        if (node->right != NULL)
            nodes.push({node->right, distance + 1});
    }

    for (const auto& [distance, value] : mp)
        view.push_back(value);

    return view;
}

void printView(const string& label, const vector<int>& view) {
    cout << label;
    for (int value : view)
        cout << value << " ";
    cout << '\n';
}

void deleteTree(Node* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<int>arr;
    int n;
    while(cin>>n && n!=-2){
        arr.push_back(n);
    }
    Node* root = insert(arr);

    vector<int> left, right;
    leftView(root, left, 0);
    rightView(root, right, 0);

    cout << "Inorder: ";
    inorder(root);
    cout << '\n';
    printView("Top view: ", topView(root));
    printView("Left view: ", left);
    printView("Right view: ", right);
    printView("Bottom view: ", bottomView(root));

    deleteTree(root);
    return 0;
}