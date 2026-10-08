#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(const vector<int>& values) {
    if (values.empty() || values[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < values.size() && values[i] != -1) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != -1) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

void printInorder(TreeNode* root) {
    if (root == nullptr) return;

    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    vector<int> values;
    int value;

    // Values EOF tak read hongi
    while (cin >> value && value != -2) {
    values.push_back(value);
}

    TreeNode* root = buildTree(values);

    cout << "Inorder: ";
    printInorder(root);
    cout << '\n';

    return 0;
}