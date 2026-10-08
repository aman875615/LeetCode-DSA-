#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Level-order values se tree build karta hai.
// -1 ka matlab missing/null node.
TreeNode* buildTree(const vector<int>& values) {
    if (values.empty() || values[0] == -1) {
        return nullptr;
    }

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

class Solution {
private:
    int heightForBalance(TreeNode* root) {
        if (root == nullptr) return 0;

        int leftHeight = heightForBalance(root->left);
        if (leftHeight == -1) return -1;

        int rightHeight = heightForBalance(root->right);
        if (rightHeight == -1) return -1;

        if (abs(leftHeight - rightHeight) > 1) return -1;

        return 1 + max(leftHeight, rightHeight);
    }

    int maxPathGain(TreeNode* root, long long& best) {
        if (root == nullptr) return 0;

        int leftGain = max(0, maxPathGain(root->left, best));
        int rightGain = max(0, maxPathGain(root->right, best));

        best = max(best, (long long)root->val + leftGain + rightGain);

        return root->val + max(leftGain, rightGain);
    }

    bool isMirror(TreeNode* a, TreeNode* b) {
        if (a == nullptr || b == nullptr) {
            return a == b;
        }

        return a->val == b->val &&
               isMirror(a->left, b->right) &&
               isMirror(a->right, b->left);
    } 

    bool checkChildrenSum(TreeNode* root) {
        if (root == nullptr) return true;

        if (root->left == nullptr && root->right == nullptr) {
            return true;
        }

        int childSum = 0;
        if (root->left != nullptr) childSum += root->left->val;
        if (root->right != nullptr) childSum += root->right->val;

        return root->val == childSum &&
               checkChildrenSum(root->left) &&
               checkChildrenSum(root->right);
    }

    void enforceChildrenSum(TreeNode* root) {
        if (root == nullptr ||
            (root->left == nullptr && root->right == nullptr)) {
            return;
        }

        int childSum = 0;
        if (root->left != nullptr) childSum += root->left->val;
        if (root->right != nullptr) childSum += root->right->val;

        // Parent ya children mein se bade value ko neeche propagate karo.
        if (childSum >= root->val) {
            root->val = childSum;
        } else {
            if (root->left != nullptr) {
                root->left->val = root->val;
            } else {
                root->right->val = root->val;
            }
        }

        enforceChildrenSum(root->left);
        enforceChildrenSum(root->right);

        // Children update hone ke baad parent ko unka sum banao.
        int total = 0;
        if (root->left != nullptr) total += root->left->val;
        if (root->right != nullptr) total += root->right->val;
        root->val = total;
    }

public:
    // 1. Maximum depth: nodes ki count
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    // 2. Check if two trees are identical
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr || q == nullptr) {
            return p == q;
        }

        return p->val == q->val &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }

    // 3. Check whether tree is height-balanced
    bool isBalanced(TreeNode* root) {
        return heightForBalance(root) != -1;
    }

    // 4. Diameter in number of edges
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;

        function<int(TreeNode*)> height = [&](TreeNode* node) {
            if (node == nullptr) return 0;

            int leftHeight = height(node->left);
            int rightHeight = height(node->right);

            diameter = max(diameter, leftHeight + rightHeight);
            return 1 + max(leftHeight, rightHeight);
        };

        height(root);
        return diameter;
    }

    // 5. Maximum path sum
    int maxPathSum(TreeNode* root) {
        if (root == nullptr) return 0;

        long long best = LLONG_MIN;
        maxPathGain(root, best);
        return (int)best;
    }

    // 6. Check whether tree is symmetric
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isMirror(root->left, root->right);
    }

    // 7a. Check Children Sum Property
    bool hasChildrenSumProperty(TreeNode* root) {
        return checkChildrenSum(root);
    }

    // 7b. Modify tree so it satisfies Children Sum Property.
    // This operation only increases node values.
    void changeTree(TreeNode* root) {
        enforceChildrenSum(root);
    }
};

// Print tree in level-order, including null markers.
void printLevelOrder(TreeNode* root) {
    if (root == nullptr) {
        cout << "Empty tree\n";
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current == nullptr) {
            cout << "N ";
            continue;
        }

        cout << current->val << " ";
        q.push(current->left);
        q.push(current->right);
    }

    cout << '\n';
}

int main() {
    // Example tree:
    //         1
    //       /   \
    //      2     3
    //     / \     \
    //    4   5     6
    //
    // -1 means there is no node at that position.
    vector<int> levelOrder = {1, 2, 3, 4, 5, -1, 6};

    TreeNode* root = buildTree(levelOrder);

    Solution sol;

    cout << "Maximum depth: "
         << sol.maxDepth(root) << '\n';

    cout << "Is balanced: "
         << (sol.isBalanced(root) ? "Yes" : "No") << '\n';

    cout << "Diameter (edges): "
         << sol.diameterOfBinaryTree(root) << '\n';

    cout << "Maximum path sum: "
         << sol.maxPathSum(root) << '\n';

    cout << "Is symmetric: "
         << (sol.isSymmetric(root) ? "Yes" : "No") << '\n';

    cout << "Children Sum Property before change: "
         << (sol.hasChildrenSumProperty(root) ? "Yes" : "No") << '\n';

    sol.changeTree(root);

    cout << "Children Sum Property after change: "
         << (sol.hasChildrenSumProperty(root) ? "Yes" : "No") << '\n';

    cout << "Tree after Children Sum update (level order):\n";
    printLevelOrder(root);

    return 0;
}