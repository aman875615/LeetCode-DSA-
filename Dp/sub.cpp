// ===== MASTER DSA - COMPLETE DP SOLUTIONS =====
#include<bits/stdc++.h>
using namespace std;

// ===== 1. LONGEST COMMON SUBSEQUENCE (LCS) =====
int lcs(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

// ===== 2. PRINT LONGEST COMMON SUBSEQUENCE =====
string printLCS(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    string lcs = "";
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if(a[i-1] == b[j-1]) {
            lcs = a[i-1] + lcs;
            i--; j--;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

// ===== 3. LONGEST COMMON SUBSTRING =====
int longestCommonSubstring(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    int maxLen = 0;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                maxLen = max(maxLen, dp[i][j]);
            }
        }
    }
    return maxLen;
}

// ===== 4. LONGEST PALINDROMIC SUBSEQUENCE =====
int longestPalindromeSubsequence(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return lcs(s, rev);
}

// ===== 5. MINIMUM INSERTIONS TO MAKE STRING PALINDROME =====
int minInsertionsForPalindrome(string s) {
    int n = s.size();
    string rev = s;
    reverse(rev.begin(), rev.end());
    int lcsLen = lcs(s, rev);
    return n - lcsLen;
}

// ===== 6. MINIMUM INSERTIONS OR DELETIONS (CONVERT A TO B) =====
int minOperationsConvert(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    // Base cases
    for(int i = 0; i <= m; i++) dp[i][0] = i;
    for(int j = 0; j <= n; j++) dp[0][j] = j;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    return dp[m][n];
}

// ===== 7. SHORTEST COMMON SUPERSEQUENCE =====
string shortestCommonSupersequence(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    string result = "";
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if(a[i-1] == b[j-1]) {
            result = a[i-1] + result;
            i--; j--;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            result = a[i-1] + result;
            i--;
        } else {
            result = b[j-1] + result;
            j--;
        }
    }
    while(i > 0) {
        result = a[i-1] + result;
        i--;
    }
    while(j > 0) {
        result = b[j-1] + result;
        j--;
    }
    return result;
}

// ===== 8. DISTINCT SUBSEQUENCES =====
int distinctSubsequences(string s) {
    int n = s.size();
    vector<long long> dp(n+1);
    dp[0] = 1; // empty subsequence
    
    vector<int> lastOccurrence(256, -1);
    
    for(int i = 1; i <= n; i++) {
        dp[i] = (dp[i-1] * 2) % 1e9;
        
        int lastPos = lastOccurrence[s[i-1]];
        if(lastPos != -1) {
            dp[i] = (dp[i] - dp[lastPos] + 1e9) % (int)1e9;
        }
        lastOccurrence[s[i-1]] = i-1;
    }
    return dp[n];
}

// ===== 9. EDIT DISTANCE (LEVENSHTEIN) =====
int editDistance(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i = 0; i <= m; i++) dp[i][0] = i;
    for(int j = 0; j <= n; j++) dp[0][j] = j;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    return dp[m][n];
}

// ===== 10. WILDCARD MATCHING =====
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    
    dp[0][0] = true;
    
    // Handle patterns like a*, a*b*, a*b*c*
    for(int j = 1; j <= n; j++) {
        if(p[j-1] == '*') {
            dp[0][j] = dp[0][j-1];
        }
    }
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(p[j-1] == '*') {
                // * matches empty or one/more characters
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            } else if(p[j-1] == '?' || s[i-1] == p[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }
    return dp[m][n];
}

// ===== 11. BEST TIME TO BUY AND SELL STOCK (DP on Stocks) =====
int maxProfitOneTransaction(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for(int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}

// ===== 12. BEST TIME TO BUY AND SELL STOCK II (Multiple Transactions) =====
int maxProfitMultipleTransactions(vector<int>& prices) {
    int maxProfit = 0;
    for(int i = 1; i < prices.size(); i++) {
        if(prices[i] > prices[i-1]) {
            maxProfit += prices[i] - prices[i-1];
        }
    }
    return maxProfit;
}

// ===== 13. BEST TIME TO BUY AND SELL STOCK III (At Most 2 Transactions) =====
int maxProfitTwoTransactions(vector<int>& prices) {
    int n = prices.size();
    if(n < 2) return 0;
    
    vector<int> left(n, 0);  // max profit with 1 transaction in [0..i]
    vector<int> right(n, 0); // max profit with 1 transaction in [i..n-1]
    
    int minPrice = prices[0];
    for(int i = 1; i < n; i++) {
        minPrice = min(minPrice, prices[i]);
        left[i] = max(left[i-1], prices[i] - minPrice);
    }
    
    int maxPrice = prices[n-1];
    for(int i = n-2; i >= 0; i--) {
        maxPrice = max(maxPrice, prices[i]);
        right[i] = max(right[i+1], maxPrice - prices[i]);
    }
    
    int maxProfit = 0;
    for(int i = 0; i < n; i++) {
        maxProfit = max(maxProfit, left[i] + right[i]);
    }
    return maxProfit;
}

// ===== 14. BEST TIME TO BUY AND SELL STOCK IV (At Most K Transactions) =====
int maxProfitKTransactions(int k, vector<int>& prices) {
    int n = prices.size();
    if(n < 2 || k == 0) return 0;
    
    if(2*k >= n) {
        // Can do unlimited transactions
        return maxProfitMultipleTransactions(prices);
    }
    
    vector<vector<int>> dp(k+1, vector<int>(n, 0));
    
    for(int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for(int j = 1; j < n; j++) {
            dp[i][j] = max(dp[i][j-1], prices[j] + maxDiff);
            maxDiff = max(maxDiff, dp[i-1][j-1] - prices[j]);
        }
    }
    return dp[k][n-1];
}

// ===== 15. COIN CHANGE (BONUS) =====
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, INT_MAX);
    dp[0] = 0;
    
    for(int coin : coins) {
        for(int i = coin; i <= amount; i++) {
            if(dp[i-coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i-coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ===== TEST FUNCTION =====
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test cases
    cout << "===== DP SOLUTIONS TEST =====" << endl;
    
    // 1. LCS
    cout << "\n1. LCS: " << lcs("abcde", "ace") << endl;
    
    // 2. Print LCS
    cout << "2. Print LCS: " << printLCS("AGGTAB", "GXTXAYB") << endl;
    
    // 3. Longest Common Substring
    cout << "3. LCS Length: " << longestCommonSubstring("abcdxyz", "xyzabcd") << endl;
    
    // 4. Longest Palindrome Subsequence
    cout << "4. Longest Palindrome: " << longestPalindromeSubsequence("abacabad") << endl;
    
    // 5. Min Insertions for Palindrome
    cout << "5. Min Insertions: " << minInsertionsForPalindrome("abcda") << endl;
    
    // 6. Edit Distance
    cout << "6. Edit Distance: " << editDistance("horse", "ros") << endl;
    
    // 7. Wildcard Matching
    cout << "7. Wildcard Match: " << (isMatch("aa", "a") ? "true" : "false") << endl;
    cout << "   Wildcard Match: " << (isMatch("aa", "*") ? "true" : "false") << endl;
    
    // 8. Stock profit
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "8. Max Profit (1 trans): " << maxProfitOneTransaction(prices) << endl;
    cout << "   Max Profit (multi): " << maxProfitMultipleTransactions(prices) << endl;
    
    return 0;
}