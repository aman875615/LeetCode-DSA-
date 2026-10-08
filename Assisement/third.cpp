#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minPathSum(vector<vector<int>>& grid, int k) {
        if (grid.empty() || grid[0].empty() || k < 0)
            return -1;

        int rows = grid.size();
        int cols = grid[0].size();
        k = min(k, 2 * min(rows - 1, cols - 1));

        const long long INF = LLONG_MAX / 4;
        vector<vector<vector<long long>>> dp(
            cols, vector<vector<long long>>(3, vector<long long>(k + 1, INF)));
        dp[0][0][0] = grid[0][0];

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (row == 0 && col == 0)
                    continue;

                vector<vector<long long>> current(
                    3, vector<long long>(k + 1, INF));

                for (int direction = 0; direction < 3; direction++) {
                    for (int turns = 0; turns <= k; turns++) {
                        if (row > 0 && dp[col][direction][turns] != INF) {
                            int newTurns = turns + (direction == 2);
                            if (newTurns <= k)
                                current[1][newTurns] = min(current[1][newTurns],
                                    dp[col][direction][turns] + grid[row][col]);
                        }

                        if (col > 0 && dp[col - 1][direction][turns] != INF) {
                            int newTurns = turns + (direction == 1);
                            if (newTurns <= k)
                                current[2][newTurns] = min(current[2][newTurns],
                                    dp[col - 1][direction][turns] + grid[row][col]);
                        }
                    }
                }

                dp[col] = move(current);
            }
        }

        long long answer = INF;
        for (int direction = 1; direction <= 2; direction++)
            for (int turns = 0; turns <= k; turns++)
                answer = min(answer, dp[cols - 1][direction][turns]);

        return answer == INF ? -1 : answer;
    }
};

int main() {
    int rows, cols, k;
    cin >> rows >> cols >> k;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            cin >> grid[row][col];

    Solution solution;
    cout << solution.minPathSum(grid, k) << '\n';
    return 0;
}