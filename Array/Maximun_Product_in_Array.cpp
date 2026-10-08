#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxEnding = nums[0];
        int minEnding = nums[0];
        int answer = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            int value = nums[i];

            if (value < 0) {
                swap(maxEnding, minEnding);
            }

            maxEnding = max(value, maxEnding * value);
            minEnding = min(value, minEnding * value);

            answer = max(answer, maxEnding);
        }

        return answer;
    }
};

int main() {
    vector<int> nums = {2, 3, -2, 4};

    Solution solution;
    cout << solution.maxProduct(nums) << '\n';  // Output: 6

    return 0;
}