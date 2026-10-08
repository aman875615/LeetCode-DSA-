#include <bits/stdc++.h>
using namespace std;

class DPAlgorithms {
    // ---------- Climbing Stairs helpers ----------
    static long long climbBrute(int n) {
        if (n <= 1) return 1;
        return climbBrute(n - 1) + climbBrute(n - 2);
    }

    static long long climbMemoHelper(int n, vector<long long>& memo) {
        if (n <= 1) return 1;
        if (memo[n] != -1) return memo[n];
        return memo[n] = climbMemoHelper(n - 1, memo) +
                         climbMemoHelper(n - 2, memo);
    }

    // ---------- Frog Jump helpers ----------
    static long long frogBruteHelper(const vector<int>& h, int i) {
        if (i == 0) return 0;
        long long one = frogBruteHelper(h, i - 1) + abs(h[i] - h[i - 1]);
        long long two = LLONG_MAX;
        if (i > 1) two = frogBruteHelper(h, i - 2) + abs(h[i] - h[i - 2]);
        return min(one, two);
    }

    static long long frogMemoHelper(const vector<int>& h, int i,
                                    vector<long long>& memo) {
        if (i == 0) return 0;
        if (memo[i] != -1) return memo[i];
        long long one = frogMemoHelper(h, i - 1, memo) + abs(h[i] - h[i - 1]);
        long long two = LLONG_MAX;
        if (i > 1) two = frogMemoHelper(h, i - 2, memo) + abs(h[i] - h[i - 2]);
        return memo[i] = min(one, two);
    }

    // ---------- K-distance Frog Jump helpers ----------
    static long long frogKBruteHelper(const vector<int>& h, int i, int k) {
        if (i == 0) return 0;
        long long best = LLONG_MAX;
        for (int jump = 1; jump <= k && i - jump >= 0; jump++) {
            best = min(best, frogKBruteHelper(h, i - jump, k) +
                             abs(h[i] - h[i - jump]));
        }
        return best;
    }

    static long long frogKMemoHelper(const vector<int>& h, int i, int k,
                                     vector<long long>& memo) {
        if (i == 0) return 0;
        if (memo[i] != -1) return memo[i];
        long long best = LLONG_MAX;
        for (int jump = 1; jump <= k && i - jump >= 0; jump++) {
            best = min(best, frogKMemoHelper(h, i - jump, k, memo) +
                             abs(h[i] - h[i - jump]));
        }
        return memo[i] = best;
    }

    // ---------- Non-adjacent sum helpers ----------
    static long long nonAdjacentBruteHelper(const vector<int>& a, int i) {
        if (i < 0) return 0;
        long long take = a[i] + nonAdjacentBruteHelper(a, i - 2);
        long long skip = nonAdjacentBruteHelper(a, i - 1);
        return max(take, skip);
    }

    static long long nonAdjacentMemoHelper(const vector<int>& a, int i,
                                          vector<long long>& memo) {
        if (i < 0) return 0;
        if (memo[i] != -1) return memo[i];
        long long take = a[i] + nonAdjacentMemoHelper(a, i - 2, memo);
        long long skip = nonAdjacentMemoHelper(a, i - 1, memo);
        return memo[i] = max(take, skip);
    }

    static long long nonAdjacentRangeBrute(const vector<int>& a, int left, int right) {
        if (left > right) return 0;
        vector<int> part(a.begin() + left, a.begin() + right + 1);
        return nonAdjacentBruteHelper(part, (int)part.size() - 1);
    }

    static long long nonAdjacentRangeMemo(const vector<int>& a, int left, int right) {
        if (left > right) return 0;
        vector<int> part(a.begin() + left, a.begin() + right + 1);
        vector<long long> memo(part.size(), -1);
        return nonAdjacentMemoHelper(part, (int)part.size() - 1, memo);
    }

    static long long nonAdjacentRangeTab(const vector<int>& a, int left, int right) {
        if (left > right) return 0;
        int len = right - left + 1;
        vector<long long> dp(len + 1, 0);
        for (int i = 1; i <= len; i++) {
            long long take = a[left + i - 1] + (i >= 2 ? dp[i - 2] : 0);
            long long skip = dp[i - 1];
            dp[i] = max(take, skip);
        }
        return dp[len];
    }

    static long long nonAdjacentRangeSpace(const vector<int>& a, int left, int right) {
        long long previousTwo = 0;
        long long previousOne = 0;
        for (int i = left; i <= right; i++) {
            long long take = a[i] + previousTwo;
            long long skip = previousOne;
            long long current = max(take, skip);
            previousTwo = previousOne;
            previousOne = current;
        }
        return previousOne;
    }

public:
    // 1. CLIMBING STAIRS
    // Brute Force: O(2^n) time, O(n) recursion stack.
    static long long climbingBrute(int n) {
        return climbBrute(n);
    }

    // Better - Memoization: O(n) time, O(n) memory + stack.
    static long long climbingMemoization(int n) {
        vector<long long> memo(n + 1, -1);
        return climbMemoHelper(n, memo);
    }

    // Tabulation: O(n) time, O(n) memory.
    static long long climbingTabulation(int n) {
        if (n <= 1) return 1;
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
        return dp[n];
    }

    // Optimal: O(n) time, O(1) extra memory.
    static long long climbingOptimal(int n) {
        if (n <= 1) return 1;
        long long twoBack = 1, oneBack = 1;
        for (int i = 2; i <= n; i++) {
            long long current = oneBack + twoBack;
            twoBack = oneBack;
            oneBack = current;
        }
        return oneBack;
    }

    // 2. FROG JUMP (jumps of 1 or 2)
    // Brute Force: O(2^n) time, O(n) recursion stack.
    static long long frogBrute(const vector<int>& heights) {
        if (heights.empty()) return 0;
        return frogBruteHelper(heights, (int)heights.size() - 1);
    }

    // Better - Memoization: O(n) time, O(n) memory + stack.
    static long long frogMemoization(const vector<int>& heights) {
        if (heights.empty()) return 0;
        vector<long long> memo(heights.size(), -1);
        return frogMemoHelper(heights, (int)heights.size() - 1, memo);
    }

    // Tabulation: O(n) time, O(n) memory.
    static long long frogTabulation(const vector<int>& h) {
        int n = h.size();
        if (n <= 1) return 0;
        vector<long long> dp(n, 0);
        for (int i = 1; i < n; i++) {
            long long one = dp[i - 1] + abs(h[i] - h[i - 1]);
            long long two = LLONG_MAX;
            if (i > 1) two = dp[i - 2] + abs(h[i] - h[i - 2]);
            dp[i] = min(one, two);
        }
        return dp[n - 1];
    }

    // Optimal: O(n) time, O(1) extra memory.
    static long long frogOptimal(const vector<int>& h) {
        int n = h.size();
        if (n <= 1) return 0;
        long long twoBack = 0, oneBack = 0;
        for (int i = 1; i < n; i++) {
            long long one = oneBack + abs(h[i] - h[i - 1]);
            long long two = LLONG_MAX;
            if (i > 1) two = twoBack + abs(h[i] - h[i - 2]);
            long long current = min(one, two);
            twoBack = oneBack;
            oneBack = current;
        }
        return oneBack;
    }

    // 3. FROG JUMP WITH K DISTANCES
    // Brute Force: exponential time, O(n) recursion stack.
    static long long frogKBrute(const vector<int>& heights, int k) {
        if (heights.empty()) return 0;
        return frogKBruteHelper(heights, (int)heights.size() - 1, k);
    }

    // Better - Memoization: O(n*k) time, O(n) memory + stack.
    static long long frogKMemoization(const vector<int>& heights, int k) {
        if (heights.empty()) return 0;
        vector<long long> memo(heights.size(), -1);
        return frogKMemoHelper(heights, (int)heights.size() - 1, k, memo);
    }

    // Tabulation: O(n*k) time, O(n) memory.
    static long long frogKTabulation(const vector<int>& h, int k) {
        int n = h.size();
        if (n <= 1) return 0;
        vector<long long> dp(n, LLONG_MAX);
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            for (int jump = 1; jump <= k && i - jump >= 0; jump++) {
                dp[i] = min(dp[i], dp[i - jump] + abs(h[i] - h[i - jump]));
            }
        }
        return dp[n - 1];
    }

    // Space-optimized: O(n*k) time, O(k) memory using a circular buffer.
    static long long frogKOptimal(const vector<int>& h, int k) {
        int n = h.size();
        if (n <= 1) return 0;
        if (k <= 0) return LLONG_MAX;
        vector<long long> recent(k + 1, LLONG_MAX);
        recent[0] = 0;
        for (int i = 1; i < n; i++) {
            long long best = LLONG_MAX;
            for (int jump = 1; jump <= k && i - jump >= 0; jump++) {
                long long prior = recent[(i - jump) % (k + 1)];
                best = min(best, prior + abs(h[i] - h[i - jump]));
            }
            recent[i % (k + 1)] = best;
        }
        return recent[(n - 1) % (k + 1)];
    }

    // 4. MAXIMUM SUM OF NON-ADJACENT ELEMENTS (linear array)
    // Brute Force: O(2^n) time, O(n) recursion stack.
    static long long nonAdjacentBrute(const vector<int>& nums) {
        return nonAdjacentBruteHelper(nums, (int)nums.size() - 1);
    }

    // Better - Memoization: O(n) time, O(n) memory + stack.
    static long long nonAdjacentMemoization(const vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<long long> memo(nums.size(), -1);
        return nonAdjacentMemoHelper(nums, (int)nums.size() - 1, memo);
    }

    // Tabulation: O(n) time, O(n) memory.
    static long long nonAdjacentTabulation(const vector<int>& nums) {
        return nonAdjacentRangeTab(nums, 0, (int)nums.size() - 1);
    }

    // Optimal: O(n) time, O(1) extra memory.
    static long long nonAdjacentOptimal(const vector<int>& nums) {
        return nonAdjacentRangeSpace(nums, 0, (int)nums.size() - 1);
    }

    // 5. HOUSE ROBBER (circular street)
    // First and last houses are adjacent. Each version splits into:
    // [0, n-2] and [1, n-1], then takes the larger result.
    // Brute Force: O(2^n) time, O(n) recursion stack.
    static long long houseRobberBrute(const vector<int>& money) {
        int n = money.size();
        if (n == 0) return 0;
        if (n == 1) return max(0, money[0]);
        return max(nonAdjacentRangeBrute(money, 0, n - 2),
                   nonAdjacentRangeBrute(money, 1, n - 1));
    }

    // Better - Memoization: O(n) time, O(n) memory + stack.
    static long long houseRobberMemoization(const vector<int>& money) {
        int n = money.size();
        if (n == 0) return 0;
        if (n == 1) return max(0, money[0]);
        return max(nonAdjacentRangeMemo(money, 0, n - 2),
                   nonAdjacentRangeMemo(money, 1, n - 1));
    }

    // Tabulation: O(n) time, O(n) memory.
    static long long houseRobberTabulation(const vector<int>& money) {
        int n = money.size();
        if (n == 0) return 0;
        if (n == 1) return max(0, money[0]);
        return max(nonAdjacentRangeTab(money, 0, n - 2),
                   nonAdjacentRangeTab(money, 1, n - 1));
    }

    // Optimal: O(n) time, O(1) extra memory.
    static long long houseRobberOptimal(const vector<int>& money) {
        int n = money.size();
        if (n == 0) return 0;
        if (n == 1) return max(0, money[0]);
        return max(nonAdjacentRangeSpace(money, 0, n - 2),
                   nonAdjacentRangeSpace(money, 1, n - 1));
    }
};

int main() {
    cout << "CLIMBING STAIRS (n = 5)\n";
    cout << "Brute: " << DPAlgorithms::climbingBrute(5) << '\n';
    cout << "Memoization: " << DPAlgorithms::climbingMemoization(5) << '\n';
    cout << "Tabulation: " << DPAlgorithms::climbingTabulation(5) << '\n';
    cout << "Optimal: " << DPAlgorithms::climbingOptimal(5) << "\n\n";

    vector<int> heights = {10, 20, 30, 10};
    cout << "FROG JUMP\n";
    cout << "Brute: " << DPAlgorithms::frogBrute(heights) << '\n';
    cout << "Memoization: " << DPAlgorithms::frogMemoization(heights) << '\n';
    cout << "Tabulation: " << DPAlgorithms::frogTabulation(heights) << '\n';
    cout << "Optimal: " << DPAlgorithms::frogOptimal(heights) << "\n\n";

    vector<int> heightsK = {10, 30, 40, 50, 20};
    int k = 3;
    cout << "FROG JUMP WITH K = " << k << "\n";
    cout << "Brute: " << DPAlgorithms::frogKBrute(heightsK, k) << '\n';
    cout << "Memoization: " << DPAlgorithms::frogKMemoization(heightsK, k) << '\n';
    cout << "Tabulation: " << DPAlgorithms::frogKTabulation(heightsK, k) << '\n';
    cout << "Space-optimized: " << DPAlgorithms::frogKOptimal(heightsK, k) << "\n\n";

    vector<int> values = {2, 1, 4, 9};
    cout << "MAXIMUM SUM OF NON-ADJACENT ELEMENTS\n";
    cout << "Brute: " << DPAlgorithms::nonAdjacentBrute(values) << '\n';
    cout << "Memoization: " << DPAlgorithms::nonAdjacentMemoization(values) << '\n';
    cout << "Tabulation: " << DPAlgorithms::nonAdjacentTabulation(values) << '\n';
    cout << "Optimal: " << DPAlgorithms::nonAdjacentOptimal(values) << "\n\n";

    vector<int> houses = {2, 3, 2};
    cout << "HOUSE ROBBER (circular)\n";
    cout << "Brute: " << DPAlgorithms::houseRobberBrute(houses) << '\n';
    cout << "Memoization: " << DPAlgorithms::houseRobberMemoization(houses) << '\n';
    cout << "Tabulation: " << DPAlgorithms::houseRobberTabulation(houses) << '\n';
    cout << "Optimal: " << DPAlgorithms::houseRobberOptimal(houses) << '\n';

    return 0;
}
