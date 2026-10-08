#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int value) : val(value), next(nullptr) {}
};

class Solution {
public:
    ListNode* findCycleStart(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }

    int lengthUntil(ListNode* head, ListNode* stop) {
        int length = 0;
        while (head != stop) {
            head = head->next;
            length++;
        }
        return length;
    }

    ListNode* findIntersection(ListNode* headA, ListNode* headB,
                               ListNode* cycleA, ListNode* cycleB) {
        if (cycleA == nullptr && cycleB == nullptr) {
            int lengthA = lengthUntil(headA, nullptr);
            int lengthB = lengthUntil(headB, nullptr);

            while (lengthA > lengthB) {
                headA = headA->next;
                lengthA--;
            }
            while (lengthB > lengthA) {
                headB = headB->next;
                lengthB--;
            }

            while (headA != headB) {
                headA = headA->next;
                headB = headB->next;
            }
            return headA;
        }

        if ((cycleA == nullptr) != (cycleB == nullptr))
            return nullptr;

        if (cycleA == cycleB) {
            int lengthA = lengthUntil(headA, cycleA);
            int lengthB = lengthUntil(headB, cycleB);

            while (lengthA > lengthB) {
                headA = headA->next;
                lengthA--;
            }
            while (lengthB > lengthA) {
                headB = headB->next;
                lengthB--;
            }

            while (headA != headB && headA != cycleA) {
                headA = headA->next;
                headB = headB->next;
            }
            return headA == headB ? headA : cycleA;
        }

        ListNode* node = cycleA->next;
        while (node != cycleA && node != cycleB)
            node = node->next;

        return node == cycleB ? cycleA : nullptr;
    }
};

int main() {
    int nodeCount;
    if (!(cin >> nodeCount) || nodeCount < 0) {
        cerr << "Invalid node count\n";
        return 1;
    }

    vector<int> values(nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        if (!(cin >> values[i])) {
            cerr << "Missing node values\n";
            return 1;
        }
    }

    vector<int> nextIndices(nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        if (!(cin >> nextIndices[i]) || nextIndices[i] < -1 || nextIndices[i] >= nodeCount) {
            cerr << "Invalid next index\n";
            return 1;
        }
    }

    int headAIndex, headBIndex;
    if (!(cin >> headAIndex >> headBIndex) ||
        headAIndex < -1 || headAIndex >= nodeCount ||
        headBIndex < -1 || headBIndex >= nodeCount) {
        cerr << "Invalid head index\n";
        return 1;
    }

    vector<ListNode*> nodes(nodeCount);
    for (int i = 0; i < nodeCount; i++)
        nodes[i] = new ListNode(values[i]);
    for (int i = 0; i < nodeCount; i++)
        if (nextIndices[i] != -1)
            nodes[i]->next = nodes[nextIndices[i]];

    ListNode* headA = headAIndex == -1 ? nullptr : nodes[headAIndex];
    ListNode* headB = headBIndex == -1 ? nullptr : nodes[headBIndex];

    Solution solution;
    ListNode* cycleA = solution.findCycleStart(headA);
    ListNode* cycleB = solution.findCycleStart(headB);
    ListNode* intersection = solution.findIntersection(headA, headB, cycleA, cycleB);

    vector<int> answer = {
        intersection == nullptr ? -1 : intersection->val,
        cycleA == nullptr ? -1 : cycleA->val,
        cycleB == nullptr ? -1 : cycleB->val
    };

    cout << "[" << answer[0] << ", " << answer[1] << ", " << answer[2] << "]\n";

    for (ListNode* node : nodes)
        delete node;
    return 0;
}