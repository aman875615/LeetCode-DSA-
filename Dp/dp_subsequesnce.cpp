#include <bits/stdc++.h>
using namespace std;

class SubsetKnapsackDP {
    static constexpr int INF = 1'000'000'000;

    // Boolean subset-sum recursion.
    static bool subsetBruteRec(const vector<int>& a, int i, int target) {
        if (target == 0) return true;
        if (i == 0) return a[0] == target;
        bool skip = subsetBruteRec(a, i - 1, target);
        bool take = false;
        if (a[i] <= target) take = subsetBruteRec(a, i - 1, target - a[i]);
        return skip || take;
    }

    static bool subsetMemoRec(const vector<int>& a, int i, int target,
                              vector<vector<int>>& memo) {
        if (target == 0) return true;
        if (i == 0) return a[0] == target;
        int& saved = memo[i][target];
        if (saved != -1) return saved;
        bool skip = subsetMemoRec(a, i - 1, target, memo);
        bool take = false;
        if (a[i] <= target) take = subsetMemoRec(a, i - 1, target - a[i], memo);
        return saved = (skip || take);
    }

    static long long countBruteRec(const vector<int>& a, int i, int target) {
        if (i == 0) {
            if (target == 0 && a[0] == 0) return 2;
            if (target == 0 || target == a[0]) return 1;
            return 0;
        }
        long long ways = countBruteRec(a, i - 1, target);
        if (a[i] <= target) ways += countBruteRec(a, i - 1, target - a[i]);
        return ways;
    }

    static long long countMemoRec(const vector<int>& a, int i, int target,
                                  vector<vector<long long>>& memo) {
        if (i == 0) {
            if (target == 0 && a[0] == 0) return 2;
            if (target == 0 || target == a[0]) return 1;
            return 0;
        }
        long long& saved = memo[i][target];
        if (saved != -1) return saved;
        saved = countMemoRec(a, i - 1, target, memo);
        if (a[i] <= target) saved += countMemoRec(a, i - 1, target - a[i], memo);
        return saved;
    }

    static long long countTabInternal(const vector<int>& a, int target) {
        int n = a.size();
        vector<vector<long long>> dp(n, vector<long long>(target + 1, 0));
        dp[0][0] = (a[0] == 0 ? 2 : 1);
        if (a[0] != 0 && a[0] <= target) dp[0][a[0]] = 1;
        for (int i = 1; i < n; i++) {
            for (int sum = 0; sum <= target; sum++) {
                dp[i][sum] = dp[i - 1][sum];
                if (a[i] <= sum) dp[i][sum] += dp[i - 1][sum - a[i]];
            }
        }
        return dp[n - 1][target];
    }

    static long long countSpaceInternal(const vector<int>& a, int target) {
        vector<long long> dp(target + 1, 0);
        dp[0] = 1;
        for (int value : a) {
            for (int sum = target; sum >= value; sum--) {
                dp[sum] += dp[sum - value];
            }
        }
        return dp[target];
    }

    static int minCoinsBruteRec(const vector<int>& coins, int i, int target) {
        if (i == 0) return target % coins[0] == 0 ? target / coins[0] : INF;
        int skip = minCoinsBruteRec(coins, i - 1, target);
        int take = INF;
        if (coins[i] <= target) take = 1 + minCoinsBruteRec(coins, i, target - coins[i]);
        return min(skip, take);
    }

    static int minCoinsMemoRec(const vector<int>& coins, int i, int target,
                               vector<vector<int>>& memo) {
        if (i == 0) return target % coins[0] == 0 ? target / coins[0] : INF;
        int& saved = memo[i][target];
        if (saved != -1) return saved;
        int skip = minCoinsMemoRec(coins, i - 1, target, memo);
        int take = INF;
        if (coins[i] <= target) take = 1 + minCoinsMemoRec(coins, i, target - coins[i], memo);
        return saved = min(skip, take);
    }

    static long long coinWaysBruteRec(const vector<int>& coins, int i, int target) {
        if (i == 0) return target % coins[0] == 0;
        long long ways = coinWaysBruteRec(coins, i - 1, target);
        if (coins[i] <= target) ways += coinWaysBruteRec(coins, i, target - coins[i]);
        return ways;
    }

    static long long coinWaysMemoRec(const vector<int>& coins, int i, int target,
                                     vector<vector<long long>>& memo) {
        if (i == 0) return target % coins[0] == 0;
        long long& saved = memo[i][target];
        if (saved != -1) return saved;
        saved = coinWaysMemoRec(coins, i - 1, target, memo);
        if (coins[i] <= target) saved += coinWaysMemoRec(coins, i, target - coins[i], memo);
        return saved;
    }

    static long long knapsackBruteRec(const vector<int>& weight,
                                      const vector<int>& value,
                                      int i, int capacity) {
        if (i == 0) return (capacity / weight[0]) * (long long)value[0];
        long long skip = knapsackBruteRec(weight, value, i - 1, capacity);
        long long take = LLONG_MIN / 4;
        if (weight[i] <= capacity)
            take = value[i] + knapsackBruteRec(weight, value, i, capacity - weight[i]);
        return max(skip, take);
    }

    static long long knapsackMemoRec(const vector<int>& weight,
                                     const vector<int>& value,
                                     int i, int capacity,
                                     vector<vector<long long>>& memo) {
        if (i == 0) return (capacity / weight[0]) * (long long)value[0];
        long long& saved = memo[i][capacity];
        if (saved != LLONG_MIN) return saved;
        long long skip = knapsackMemoRec(weight, value, i - 1, capacity, memo);
        long long take = LLONG_MIN / 4;
        if (weight[i] <= capacity)
            take = value[i] + knapsackMemoRec(weight, value, i, capacity - weight[i], memo);
        return saved = max(skip, take);
    }

public:
    // 1. Subset Sum Equal to Target
    // Brute O(2^n), memo/tabulation O(n*target), optimal O(n*target) time/O(target) space.
    static bool subsetSumBrute(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        return subsetBruteRec(a, (int)a.size() - 1, target);
    }

    static bool subsetSumMemoization(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        vector<vector<int>> memo(a.size(), vector<int>(target + 1, -1));
        return subsetMemoRec(a, (int)a.size() - 1, target, memo);
    }

    static bool subsetSumTabulation(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        int n = a.size();
        vector<vector<char>> dp(n, vector<char>(target + 1, false));
        for (int i = 0; i < n; i++) dp[i][0] = true;
        if (a[0] <= target) dp[0][a[0]] = true;
        for (int i = 1; i < n; i++) {
            for (int sum = 1; sum <= target; sum++) {
                dp[i][sum] = dp[i - 1][sum];
                if (a[i] <= sum) dp[i][sum] = dp[i][sum] || dp[i - 1][sum - a[i]];
            }
        }
        return dp[n - 1][target];
    }

    static bool subsetSumOptimal(const vector<int>& a, int target) {
        vector<char> dp(target + 1, false);
        dp[0] = true;
        for (int value : a) {
            for (int sum = target; sum >= value; sum--)
                dp[sum] = dp[sum] || dp[sum - value];
        }
        return dp[target];
    }

    // 2. Partition Equal Subset Sum: split into two equal-sum subsets.
    static bool partitionEqualBrute(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        return total % 2 == 0 && subsetSumBrute(a, total / 2);
    }
    static bool partitionEqualMemoization(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        return total % 2 == 0 && subsetSumMemoization(a, total / 2);
    }
    static bool partitionEqualTabulation(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        return total % 2 == 0 && subsetSumTabulation(a, total / 2);
    }
    static bool partitionEqualOptimal(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        return total % 2 == 0 && subsetSumOptimal(a, total / 2);
    }

    // 3. Minimum Subset Sum Difference.
    // Brute Force O(2^n).
    static long long minDifferenceBrute(const vector<int>& a) {
        function<long long(int, long long)> rec = [&](int i, long long sum) -> long long {
            if (i == (int)a.size()) {
                long long total = accumulate(a.begin(), a.end(), 0LL);
                return llabs(total - 2 * sum);
            }
            return min(rec(i + 1, sum), rec(i + 1, sum + a[i]));
        };
        return rec(0, 0);
    }

    // Memoization and tabulation use subset-sum states: O(n*total) time/space.
    static long long minDifferenceMemoization(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        vector<vector<int>> memo(a.size(), vector<int>(total + 1, -1));
        function<bool(int, int)> can = [&](int i, int sum) {
            if (sum == 0) return true;
            if (i == 0) return a[0] == sum;
            int& saved = memo[i][sum];
            if (saved != -1) return (bool)saved;
            bool result = can(i - 1, sum);
            if (a[i] <= sum) result = result || can(i - 1, sum - a[i]);
            saved = result;
            return result;
        };
        long long answer = LLONG_MAX;
        for (int sum = 0; sum <= total / 2; sum++)
            if (can((int)a.size() - 1, sum)) answer = min(answer, (long long)total - 2LL * sum);
        return answer == LLONG_MAX ? 0 : answer;
    }

    static long long minDifferenceTabulation(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        vector<vector<char>> dp(a.size(), vector<char>(total + 1, false));
        for (int i = 0; i < (int)a.size(); i++) dp[i][0] = true;
        if (!a.empty() && a[0] <= total) dp[0][a[0]] = true;
        for (int i = 1; i < (int)a.size(); i++)
            for (int sum = 1; sum <= total; sum++) {
                dp[i][sum] = dp[i - 1][sum];
                if (a[i] <= sum) dp[i][sum] = dp[i][sum] || dp[i - 1][sum - a[i]];
            }
        long long answer = LLONG_MAX;
        for (int sum = 0; sum <= total / 2; sum++)
            if (dp.back()[sum]) answer = min(answer, (long long)total - 2LL * sum);
        return answer == LLONG_MAX ? 0 : answer;
    }

    // Optimal extra space O(total); time O(n*total).
    static long long minDifferenceOptimal(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        vector<char> dp(total + 1, false);
        dp[0] = true;
        for (int value : a)
            for (int sum = total; sum >= value; sum--)
                dp[sum] = dp[sum] || dp[sum - value];
        long long answer = LLONG_MAX;
        for (int sum = 0; sum <= total / 2; sum++)
            if (dp[sum]) answer = min(answer, (long long)total - 2LL * sum);
        return answer == LLONG_MAX ? 0 : answer;
    }

    // 4. Count Subsets with Sum K. Zeros count as separate include/exclude choices.
    // Brute O(2^n); memo/tab/space O(n*k) time, space versions O(k).
    static long long countSubsetsBrute(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        return countBruteRec(a, (int)a.size() - 1, target);
    }
    static long long countSubsetsMemoization(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        vector<vector<long long>> memo(a.size(), vector<long long>(target + 1, -1));
        return countMemoRec(a, (int)a.size() - 1, target, memo);
    }
    static long long countSubsetsTabulation(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        return countTabInternal(a, target);
    }
    static long long countSubsetsOptimal(const vector<int>& a, int target) {
        return countSpaceInternal(a, target);
    }

    // 5. Count Partitions with Given Difference: S1 - S2 = difference.
    // Transform to count subsets with sum (total + difference) / 2.
private:
    static long long partitionCountBruteHelper(const vector<int>& a, int target) {
        return a.empty() ? (target == 0) : countBruteRec(a, (int)a.size() - 1, target);
    }
    static long long partitionCountMemoHelper(const vector<int>& a, int target) {
        if (a.empty()) return target == 0;
        vector<vector<long long>> memo(a.size(), vector<long long>(target + 1, -1));
        return countMemoRec(a, (int)a.size() - 1, target, memo);
    }
public:
    static long long countPartitionsBrute(const vector<int>& a, int difference) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + difference;
        if (numerator < 0 || numerator % 2) return 0;
        return partitionCountBruteHelper(a, (int)(numerator / 2));
    }
    static long long countPartitionsMemoization(const vector<int>& a, int difference) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + difference;
        if (numerator < 0 || numerator % 2) return 0;
        return partitionCountMemoHelper(a, (int)(numerator / 2));
    }
    static long long countPartitionsTabulation(const vector<int>& a, int difference) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + difference;
        if (numerator < 0 || numerator % 2) return 0;
        return countTabInternal(a, (int)(numerator / 2));
    }
    static long long countPartitionsOptimal(const vector<int>& a, int difference) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + difference;
        if (numerator < 0 || numerator % 2) return 0;
        return countSpaceInternal(a, (int)(numerator / 2));
    }

    // 6. Assign Cookies. Greedy: sort both arrays, satisfy smallest appetite first.
    // O(n log n + m log m) time, O(1) extra space aside from sorting.
    static int assignCookies(vector<int> greed, vector<int> cookies) {
        sort(greed.begin(), greed.end());
        sort(cookies.begin(), cookies.end());
        int child = 0, cookie = 0;
        while (child < (int)greed.size() && cookie < (int)cookies.size()) {
            if (cookies[cookie] >= greed[child]) child++;
            cookie++;
        }
        return child;
    }

    // 7. Minimum Coins (unlimited supply of each coin).
    // Brute exponential; memo/tab O(n*target); space optimized O(target).
    static int minimumCoinsBrute(const vector<int>& coins, int target) {
        if (coins.empty()) return target == 0 ? 0 : -1;
        int answer = minCoinsBruteRec(coins, (int)coins.size() - 1, target);
        return answer >= INF ? -1 : answer;
    }
    static int minimumCoinsMemoization(const vector<int>& coins, int target) {
        if (coins.empty()) return target == 0 ? 0 : -1;
        vector<vector<int>> memo(coins.size(), vector<int>(target + 1, -1));
        int answer = minCoinsMemoRec(coins, (int)coins.size() - 1, target, memo);
        return answer >= INF ? -1 : answer;
    }
    static int minimumCoinsTabulation(const vector<int>& coins, int target) {
        if (coins.empty()) return target == 0 ? 0 : -1;
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, INF));
        for (int sum = 0; sum <= target; sum++)
            if (sum % coins[0] == 0) dp[0][sum] = sum / coins[0];
        for (int i = 1; i < n; i++) {
            for (int sum = 0; sum <= target; sum++) {
                int skip = dp[i - 1][sum];
                int take = INF;
                if (coins[i] <= sum && dp[i][sum - coins[i]] < INF)
                    take = 1 + dp[i][sum - coins[i]];
                dp[i][sum] = min(skip, take);
            }
        }
        return dp[n - 1][target] >= INF ? -1 : dp[n - 1][target];
    }
    static int minimumCoinsOptimal(const vector<int>& coins, int target) {
        vector<int> dp(target + 1, INF);
        dp[0] = 0;
        for (int coin : coins)
            for (int sum = coin; sum <= target; sum++)
                if (dp[sum - coin] < INF)
                    dp[sum] = min(dp[sum], 1 + dp[sum - coin]);
        return dp[target] >= INF ? -1 : dp[target];
    }

    // 8. Target Sum: assign + or - to each number to reach target.
    // Transforms into count-subsets problem. Values are assumed nonnegative.
    static long long targetSumBrute(const vector<int>& a, int target) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + target;
        if (llabs((long long)target) > total || numerator < 0 || numerator % 2) return 0;
        return countSubsetsBrute(a, (int)(numerator / 2));
    }
    static long long targetSumMemoization(const vector<int>& a, int target) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + target;
        if (llabs((long long)target) > total || numerator < 0 || numerator % 2) return 0;
        return countSubsetsMemoization(a, (int)(numerator / 2));
    }
    static long long targetSumTabulation(const vector<int>& a, int target) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + target;
        if (llabs((long long)target) > total || numerator < 0 || numerator % 2) return 0;
        return countSubsetsTabulation(a, (int)(numerator / 2));
    }
    static long long targetSumOptimal(const vector<int>& a, int target) {
        long long total = accumulate(a.begin(), a.end(), 0LL);
        long long numerator = total + target;
        if (llabs((long long)target) > total || numerator < 0 || numerator % 2) return 0;
        return countSubsetsOptimal(a, (int)(numerator / 2));
    }

    // 9. Coin Change II: number of combinations using unlimited coins.
    // Brute exponential; memo/tab O(n*amount); space optimized O(amount).
    static long long coinChangeBrute(const vector<int>& coins, int amount) {
        if (coins.empty()) return amount == 0;
        return coinWaysBruteRec(coins, (int)coins.size() - 1, amount);
    }
    static long long coinChangeMemoization(const vector<int>& coins, int amount) {
        if (coins.empty()) return amount == 0;
        vector<vector<long long>> memo(coins.size(), vector<long long>(amount + 1, -1));
        return coinWaysMemoRec(coins, (int)coins.size() - 1, amount, memo);
    }
    static long long coinChangeTabulation(const vector<int>& coins, int amount) {
        if (coins.empty()) return amount == 0;
        int n = coins.size();
        vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));
        for (int sum = 0; sum <= amount; sum++) dp[0][sum] = (sum % coins[0] == 0);
        for (int i = 1; i < n; i++) {
            for (int sum = 0; sum <= amount; sum++) {
                dp[i][sum] = dp[i - 1][sum];
                if (coins[i] <= sum) dp[i][sum] += dp[i][sum - coins[i]];
            }
        }
        return dp[n - 1][amount];
    }
    static long long coinChangeOptimal(const vector<int>& coins, int amount) {
        vector<long long> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins)
            for (int sum = coin; sum <= amount; sum++)
                dp[sum] += dp[sum - coin];
        return dp[amount];
    }

private:
    // Unbounded knapsack tabulation helper.
    static long long unboundedTabInternal(const vector<int>& weight,
                                          const vector<int>& value, int capacity) {
        if (weight.empty()) return 0;
        int n = weight.size();
        vector<vector<long long>> dp(n, vector<long long>(capacity + 1, 0));
        for (int cap = 0; cap <= capacity; cap++)
            dp[0][cap] = (cap / weight[0]) * (long long)value[0];
        for (int i = 1; i < n; i++) {
            for (int cap = 0; cap <= capacity; cap++) {
                long long skip = dp[i - 1][cap];
                long long take = LLONG_MIN / 4;
                if (weight[i] <= cap) take = value[i] + dp[i][cap - weight[i]];
                dp[i][cap] = max(skip, take);
            }
        }
        return dp[n - 1][capacity];
    }

    static long long unboundedSpaceInternal(const vector<int>& weight,
                                             const vector<int>& value, int capacity) {
        if (weight.empty()) return 0;
        vector<long long> dp(capacity + 1, 0);
        for (int cap = 0; cap <= capacity; cap++)
            dp[cap] = (cap / weight[0]) * (long long)value[0];
        for (int i = 1; i < (int)weight.size(); i++)
            for (int cap = weight[i]; cap <= capacity; cap++)
                dp[cap] = max(dp[cap], (long long)value[i] + dp[cap - weight[i]]);
        return dp[capacity];
    }

public:
    // 10. Unbounded Knapsack: each item can be picked any number of times.
    // Brute exponential; memo/tab O(n*capacity); optimal O(n*capacity) time/O(capacity) space.
    static long long unboundedKnapsackBrute(const vector<int>& weight,
                                             const vector<int>& value, int capacity) {
        if (weight.empty()) return 0;
        return knapsackBruteRec(weight, value, (int)weight.size() - 1, capacity);
    }
    static long long unboundedKnapsackMemoization(const vector<int>& weight,
                                                   const vector<int>& value, int capacity) {
        if (weight.empty()) return 0;
        vector<vector<long long>> memo(weight.size(),
                                       vector<long long>(capacity + 1, LLONG_MIN));
        return knapsackMemoRec(weight, value, (int)weight.size() - 1, capacity, memo);
    }
    static long long unboundedKnapsackTabulation(const vector<int>& weight,
                                                 const vector<int>& value, int capacity) {
        return unboundedTabInternal(weight, value, capacity);
    }
    static long long unboundedKnapsackOptimal(const vector<int>& weight,
                                               const vector<int>& value, int capacity) {
        return unboundedSpaceInternal(weight, value, capacity);
    }

    // 11. Rod Cutting: piece length can be used unlimited times.
    // price[i] is the price of a rod piece of length i+1.
    static long long rodCuttingBrute(const vector<int>& price) {
        vector<int> length(price.size());
        iota(length.begin(), length.end(), 1);
        return unboundedKnapsackBrute(length, price, (int)price.size());
    }
    static long long rodCuttingMemoization(const vector<int>& price) {
        vector<int> length(price.size());
        iota(length.begin(), length.end(), 1);
        return unboundedKnapsackMemoization(length, price, (int)price.size());
    }
    static long long rodCuttingTabulation(const vector<int>& price) {
        vector<int> length(price.size());
        iota(length.begin(), length.end(), 1);
        return unboundedKnapsackTabulation(length, price, (int)price.size());
    }
    static long long rodCuttingOptimal(const vector<int>& price) {
        vector<int> length(price.size());
        iota(length.begin(), length.end(), 1);
        return unboundedKnapsackOptimal(length, price, (int)price.size());
    }
};

int main() {
    vector<int> a = {1, 2, 3, 4};
    int target = 5;
    cout << "SUBSET SUM, target 5: " << boolalpha << '\n';
    cout << "Brute: " << SubsetKnapsackDP::subsetSumBrute(a, target) << '\n';
    cout << "Memo: " << SubsetKnapsackDP::subsetSumMemoization(a, target) << '\n';
    cout << "Tabulation: " << SubsetKnapsackDP::subsetSumTabulation(a, target) << '\n';
    cout << "Optimal: " << SubsetKnapsackDP::subsetSumOptimal(a, target) << "\n\n";

    vector<int> equalParts = {1, 5, 11, 5};
    cout << "PARTITION EQUAL, optimal: "
         << SubsetKnapsackDP::partitionEqualOptimal(equalParts) << '\n';

    vector<int> diffArray = {1, 6, 11, 5};
    cout << "MINIMUM SUBSET DIFFERENCE, optimal: "
         << SubsetKnapsackDP::minDifferenceOptimal(diffArray) << '\n';

    vector<int> countArray = {1, 2, 2, 3};
    cout << "COUNT SUBSETS SUM 3, optimal: "
         << SubsetKnapsackDP::countSubsetsOptimal(countArray, 3) << '\n';
    cout << "COUNT PARTITIONS DIFFERENCE 1, optimal: "
         << SubsetKnapsackDP::countPartitionsOptimal(countArray, 1) << '\n';

    vector<int> greed = {1, 2, 3};
    vector<int> cookies = {1, 1};
    cout << "ASSIGN COOKIES: "
         << SubsetKnapsackDP::assignCookies(greed, cookies) << '\n';

    vector<int> coins = {1, 2, 5};
    cout << "MINIMUM COINS for 11, optimal: "
         << SubsetKnapsackDP::minimumCoinsOptimal(coins, 11) << '\n';
    cout << "TARGET SUM ways for [1,1,1,1,1], target 3, optimal: "
         << SubsetKnapsackDP::targetSumOptimal({1, 1, 1, 1, 1}, 3) << '\n';
    cout << "COIN CHANGE II ways for amount 5, optimal: "
         << SubsetKnapsackDP::coinChangeOptimal(coins, 5) << '\n';

    vector<int> weights = {2, 4, 6};
    vector<int> values = {5, 11, 13};
    cout << "UNBOUNDED KNAPSACK capacity 10, optimal: "
         << SubsetKnapsackDP::unboundedKnapsackOptimal(weights, values, 10) << '\n';

    vector<int> prices = {2, 5, 7, 8, 10};
    cout << "ROD CUTTING length 5, optimal: "
         << SubsetKnapsackDP::rodCuttingOptimal(prices) << '\n';

    return 0;
}
