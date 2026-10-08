#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m,
               vector<int>& nums2, int n) {
        int i = m - 1;         // nums1 ka last valid element
        int j = n - 1;         // nums2 ka last element
        int k = m + n - 1;     // nums1 mein last position

        // Peechhe se bade element ko sahi jagah rakho
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        // nums2 ke bache hue elements copy karo
        while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};

int main() {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    int m = 3;
    int n = 3;

    Solution solution;
    solution.merge(nums1, m, nums2, n);

    for (int value : nums1) {
        cout << value << " ";
    }
    cout << '\n';

    return 0;
}