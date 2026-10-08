#include <bits/stdc++.h>
using namespace std;

class GridDP {
    static constexpr long long NEG = LLONG_MIN / 4;

    // Ninja's Training: brute helper
    static long long trainingBruteHelper(const vector<vector<int>>& points,
                                         int day, int lastTask) {
        if (day == 0) {
            long long best = 0;
            for (int task = 0; task < 3; task++) {
                if (task != lastTask) best = max(best, (long long)points[0][task]);
            }
            return best;
        }
        long long best = 0;
        for (int task = 0; task < 3; task++) {
            if (task != lastTask) {
                best = max(best, (long long)points[day][task] +
                                  trainingBruteHelper(points, day - 1, task));
            }
        }
        return best;
    }

    static long long trainingMemoHelper(const vector<vector<int>>& points,
                                        int day, int lastTask,
                                        vector<vector<long long>>& memo) {
        if (day == 0) {
            long long best = 0;
            for (int task = 0; task < 3; task++)
                if (task != lastTask) best = max(best, (long long)points[0][task]);
            return best;
        }
        if (memo[day][lastTask] != -1) return memo[day][lastTask];

        long long best = 0;
        for (int task = 0; task < 3; task++) {
            if (task != lastTask) {
                best = max(best, (long long)points[day][task] +
                                  trainingMemoHelper(points, day - 1, task, memo));
            }
        }
        return memo[day][lastTask] = best;
    }

    // Unique Paths: recursive helper
    static long long pathsBruteHelper(int r, int c) {
        if (r == 0 && c == 0) return 1;
        if (r < 0 || c < 0) return 0;
        return pathsBruteHelper(r - 1, c) + pathsBruteHelper(r, c - 1);
    }

    static long long pathsMemoHelper(int r, int c,
                                     vector<vector<long long>>& memo) {
        if (r == 0 && c == 0) return 1;
        if (r < 0 || c < 0) return 0;
        if (memo[r][c] != -1) return memo[r][c];
        return memo[r][c] = pathsMemoHelper(r - 1, c, memo) +
                            pathsMemoHelper(r, c - 1, memo);
    }

    // Unique Paths II: recursive helpers
    static long long obstacleBruteHelper(const vector<vector<int>>& grid,
                                         int r, int c) {
        if (r < 0 || c < 0 || grid[r][c] == 1) return 0;
        if (r == 0 && c == 0) return 1;
        return obstacleBruteHelper(grid, r - 1, c) +
               obstacleBruteHelper(grid, r, c - 1);
    }

    static long long obstacleMemoHelper(const vector<vector<int>>& grid,
                                        int r, int c,
                                        vector<vector<long long>>& memo) {
        if (r < 0 || c < 0 || grid[r][c] == 1) return 0;
        if (r == 0 && c == 0) return 1;
        if (memo[r][c] != -1) return memo[r][c];
        return memo[r][c] = obstacleMemoHelper(grid, r - 1, c, memo) +
                            obstacleMemoHelper(grid, r, c - 1, memo);
    }

    // Minimum Path Sum: recursive helpers
    static long long minPathBruteHelper(const vector<vector<int>>& grid,
                                        int r, int c) {
        if (r < 0 || c < 0) return LLONG_MAX / 4;
        if (r == 0 && c == 0) return grid[0][0];
        return grid[r][c] + min(minPathBruteHelper(grid, r - 1, c),
                                minPathBruteHelper(grid, r, c - 1));
    }

    static long long minPathMemoHelper(const vector<vector<int>>& grid,
                                       int r, int c,
                                       vector<vector<long long>>& memo) {
        if (r < 0 || c < 0) return LLONG_MAX / 4;
        if (r == 0 && c == 0) return grid[0][0];
        if (memo[r][c] != -1) return memo[r][c];
        return memo[r][c] = grid[r][c] +
            min(minPathMemoHelper(grid, r - 1, c, memo),
                minPathMemoHelper(grid, r, c - 1, memo));
    }

    // Triangle: recursive helpers
    static long long triangleBruteHelper(const vector<vector<int>>& t,
                                         int row, int col) {
        if (row == (int)t.size() - 1) return t[row][col];
        long long down = triangleBruteHelper(t, row + 1, col);
        long long diagonal = triangleBruteHelper(t, row + 1, col + 1);
        return t[row][col] + min(down, diagonal);
    }

    static long long triangleMemoHelper(const vector<vector<int>>& t,
                                        int row, int col,
                                        vector<vector<long long>>& memo) {
        if (row == (int)t.size() - 1) return t[row][col];
        if (memo[row][col] != LLONG_MIN) return memo[row][col];
        long long down = triangleMemoHelper(t, row + 1, col, memo);
        long long diagonal = triangleMemoHelper(t, row + 1, col + 1, memo);
        return memo[row][col] = t[row][col] + min(down, diagonal);
    }

    // Minimum Falling Path Sum: recursive helpers
    static long long fallingBruteHelper(const vector<vector<int>>& matrix,
                                        int r, int c) {
        int n = matrix.size();
        if (c < 0 || c >= n) return LLONG_MAX / 4;
        if (r == n - 1) return matrix[r][c];
        return matrix[r][c] + min({fallingBruteHelper(matrix, r + 1, c),
                                   fallingBruteHelper(matrix, r + 1, c - 1),
                                   fallingBruteHelper(matrix, r + 1, c + 1)});
    }

    static long long fallingMemoHelper(const vector<vector<int>>& matrix,
                                       int r, int c,
                                       vector<vector<long long>>& memo) {
        int n = matrix.size();
        if (c < 0 || c >= n) return LLONG_MAX / 4;
        if (r == n - 1) return matrix[r][c];
        if (memo[r][c] != LLONG_MIN) return memo[r][c];
        return memo[r][c] = matrix[r][c] +
            min({fallingMemoHelper(matrix, r + 1, c, memo),
                 fallingMemoHelper(matrix, r + 1, c - 1, memo),
                 fallingMemoHelper(matrix, r + 1, c + 1, memo)});
    }

    // Ninja and Friends / Cherry Pickup II: recursive helpers
    static long long friendsBruteHelper(const vector<vector<int>>& grid,
                                       int row, int c1, int c2) {
        int rows = grid.size(), cols = grid[0].size();
        if (c1 < 0 || c1 >= cols || c2 < 0 || c2 >= cols) return NEG;

        long long current = grid[row][c1];
        if (c1 != c2) current += grid[row][c2];
        if (row == rows - 1) return current;

        long long best = NEG;
        for (int d1 = -1; d1 <= 1; d1++) {
            for (int d2 = -1; d2 <= 1; d2++) {
                best = max(best, friendsBruteHelper(grid, row + 1,
                                                    c1 + d1, c2 + d2));
            }
        }
        return current + best;
    }

    static long long friendsMemoHelper(const vector<vector<int>>& grid,
                                       int row, int c1, int c2,
                                       vector<vector<vector<long long>>>& memo) {
        int rows = grid.size(), cols = grid[0].size();
        if (c1 < 0 || c1 >= cols || c2 < 0 || c2 >= cols) return NEG;

        long long& saved = memo[row][c1][c2];
        if (saved != LLONG_MIN) return saved;

        long long current = grid[row][c1];
        if (c1 != c2) current += grid[row][c2];
        if (row == rows - 1) return saved = current;

        long long best = NEG;
        for (int d1 = -1; d1 <= 1; d1++) {
            for (int d2 = -1; d2 <= 1; d2++) {
                best = max(best, friendsMemoHelper(grid, row + 1,
                                                   c1 + d1, c2 + d2, memo));
            }
        }
        return saved = current + best;
    }

public:
    // 1. Ninja's Training. points[day][task], 3 tasks/day; cannot repeat yesterday's task.
    // Brute: O(3^n) time, O(n) stack. Memo: O(n) time, O(n) memory.
    // Tabulation: O(n) time, O(n) memory. Optimal: O(n) time, O(1) memory.
    static long long trainingBrute(const vector<vector<int>>& points) {
        if (points.empty()) return 0;
        return trainingBruteHelper(points, (int)points.size() - 1, 3);
    }

    static long long trainingMemoization(const vector<vector<int>>& points) {
        if (points.empty()) return 0;
        vector<vector<long long>> memo(points.size(), vector<long long>(4, -1));
        return trainingMemoHelper(points, (int)points.size() - 1, 3, memo);
    }

    static long long trainingTabulation(const vector<vector<int>>& points) {
        int n = points.size();
        if (n == 0) return 0;
        vector<vector<long long>> dp(n, vector<long long>(4, 0));
        for (int last = 0; last < 4; last++) {
            for (int task = 0; task < 3; task++)
                if (task != last) dp[0][last] = max(dp[0][last], (long long)points[0][task]);
        }
        for (int day = 1; day < n; day++) {
            for (int last = 0; last < 4; last++) {
                for (int task = 0; task < 3; task++) {
                    if (task != last)
                        dp[day][last] = max(dp[day][last],
                            (long long)points[day][task] + dp[day - 1][task]);
                }
            }
        }
        return dp[n - 1][3];
    }

    static long long trainingOptimal(const vector<vector<int>>& points) {
        int n = points.size();
        if (n == 0) return 0;
        vector<long long> previous(4, 0), current(4, 0);
        for (int last = 0; last < 4; last++)
            for (int task = 0; task < 3; task++)
                if (task != last) previous[last] = max(previous[last], (long long)points[0][task]);

        for (int day = 1; day < n; day++) {
            fill(current.begin(), current.end(), 0);
            for (int last = 0; last < 4; last++)
                for (int task = 0; task < 3; task++)
                    if (task != last)
                        current[last] = max(current[last],
                            (long long)points[day][task] + previous[task]);
            previous = current;
        }
        return previous[3];
    }

    // 2. Grid Unique Paths (no obstacles). m rows, n columns.
    // Brute exponential; memo/tabulation O(m*n); optimal O(m*n) time, O(n) memory.
    static long long uniquePathsBrute(int m, int n) {
        return pathsBruteHelper(m - 1, n - 1);
    }

    static long long uniquePathsMemoization(int m, int n) {
        vector<vector<long long>> memo(m, vector<long long>(n, -1));
        return pathsMemoHelper(m - 1, n - 1, memo);
    }

    static long long uniquePathsTabulation(int m, int n) {
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (r == 0 && c == 0) dp[r][c] = 1;
                else dp[r][c] = (r > 0 ? dp[r - 1][c] : 0) +
                                (c > 0 ? dp[r][c - 1] : 0);
            }
        }
        return dp[m - 1][n - 1];
    }

    static long long uniquePathsOptimal(int m, int n) {
        vector<long long> previous(n, 0);
        for (int r = 0; r < m; r++) {
            vector<long long> current(n, 0);
            for (int c = 0; c < n; c++) {
                if (r == 0 && c == 0) current[c] = 1;
                else current[c] = (r > 0 ? previous[c] : 0) +
                                  (c > 0 ? current[c - 1] : 0);
            }
            previous = current;
        }
        return previous[n - 1];
    }

    // 3. Unique Paths II. 1 means obstacle, 0 means open cell.
    static long long uniquePathsWithObstaclesBrute(const vector<vector<int>>& grid) {
        return obstacleBruteHelper(grid, (int)grid.size() - 1,
                                   (int)grid[0].size() - 1);
    }

    static long long uniquePathsWithObstaclesMemoization(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> memo(m, vector<long long>(n, -1));
        return obstacleMemoHelper(grid, m - 1, n - 1, memo);
    }

    static long long uniquePathsWithObstaclesTabulation(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) dp[r][c] = 0;
                else if (r == 0 && c == 0) dp[r][c] = 1;
                else dp[r][c] = (r > 0 ? dp[r - 1][c] : 0) +
                                (c > 0 ? dp[r][c - 1] : 0);
            }
        }
        return dp[m - 1][n - 1];
    }

    static long long uniquePathsWithObstaclesOptimal(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<long long> dp(n, 0);
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) dp[c] = 0;
                else if (r == 0 && c == 0) dp[c] = 1;
                else if (c > 0) dp[c] += dp[c - 1];
            }
        }
        return dp[n - 1];
    }

    // 4. Minimum Path Sum in Grid. Moves: right/down.
    static long long minPathSumBrute(const vector<vector<int>>& grid) {
        return minPathBruteHelper(grid, (int)grid.size() - 1,
                                  (int)grid[0].size() - 1);
    }

    static long long minPathSumMemoization(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> memo(m, vector<long long>(n, -1));
        return minPathMemoHelper(grid, m - 1, n - 1, memo);
    }

    static long long minPathSumTabulation(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (r == 0 && c == 0) dp[r][c] = grid[r][c];
                else {
                    long long up = r > 0 ? dp[r - 1][c] : LLONG_MAX / 4;
                    long long left = c > 0 ? dp[r][c - 1] : LLONG_MAX / 4;
                    dp[r][c] = grid[r][c] + min(up, left);
                }
            }
        }
        return dp[m - 1][n - 1];
    }

    static long long minPathSumOptimal(const vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<long long> dp(n, LLONG_MAX / 4);
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (r == 0 && c == 0) dp[c] = grid[r][c];
                else {
                    long long up = r > 0 ? dp[c] : LLONG_MAX / 4;
                    long long left = c > 0 ? dp[c - 1] : LLONG_MAX / 4;
                    dp[c] = grid[r][c] + min(up, left);
                }
            }
        }
        return dp[n - 1];
    }

    // 5. Triangle minimum path sum. Move down or down-right.
    static long long triangleBrute(const vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        return triangleBruteHelper(triangle, 0, 0);
    }

    static long long triangleMemoization(const vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        vector<vector<long long>> memo(triangle.size());
        for (int r = 0; r < (int)triangle.size(); r++)
            memo[r].assign(triangle[r].size(), LLONG_MIN);
        return triangleMemoHelper(triangle, 0, 0, memo);
    }

    static long long triangleTabulation(const vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        vector<vector<long long>> dp(triangle.size());
        int last = (int)triangle.size() - 1;
        for (int c = 0; c < (int)triangle[last].size(); c++)
            dp[last].push_back(triangle[last][c]);

        for (int r = last - 1; r >= 0; r--) {
            dp[r].resize(triangle[r].size());
            for (int c = 0; c < (int)triangle[r].size(); c++)
                dp[r][c] = triangle[r][c] + min(dp[r + 1][c], dp[r + 1][c + 1]);
        }
        return dp[0][0];
    }

    static long long triangleOptimal(const vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        vector<long long> dp(triangle.back().begin(), triangle.back().end());
        for (int r = (int)triangle.size() - 2; r >= 0; r--)
            for (int c = 0; c < (int)triangle[r].size(); c++)
                dp[c] = triangle[r][c] + min(dp[c], dp[c + 1]);
        return dp[0];
    }

    // 6. Minimum Falling Path Sum. Start anywhere in top row, finish anywhere in bottom.
    static long long fallingPathBrute(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        long long answer = LLONG_MAX;
        for (int c = 0; c < (int)matrix.size(); c++)
            answer = min(answer, fallingBruteHelper(matrix, 0, c));
        return answer;
    }

    static long long fallingPathMemoization(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int n = matrix.size();
        vector<vector<long long>> memo(n, vector<long long>(n, LLONG_MIN));
        long long answer = LLONG_MAX;
        for (int c = 0; c < n; c++)
            answer = min(answer, fallingMemoHelper(matrix, 0, c, memo));
        return answer;
    }

    static long long fallingPathTabulation(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int n = matrix.size();
        vector<vector<long long>> dp(n, vector<long long>(n, 0));
        for (int c = 0; c < n; c++) dp[0][c] = matrix[0][c];
        for (int r = 1; r < n; r++) {
            for (int c = 0; c < n; c++) {
                long long up = dp[r - 1][c];
                long long leftDiag = c > 0 ? dp[r - 1][c - 1] : LLONG_MAX / 4;
                long long rightDiag = c + 1 < n ? dp[r - 1][c + 1] : LLONG_MAX / 4;
                dp[r][c] = matrix[r][c] + min({up, leftDiag, rightDiag});
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    static long long fallingPathOptimal(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int n = matrix.size();
        vector<long long> previous(matrix[0].begin(), matrix[0].end());
        for (int r = 1; r < n; r++) {
            vector<long long> current(n);
            for (int c = 0; c < n; c++) {
                long long up = previous[c];
                long long leftDiag = c > 0 ? previous[c - 1] : LLONG_MAX / 4;
                long long rightDiag = c + 1 < n ? previous[c + 1] : LLONG_MAX / 4;
                current[c] = matrix[r][c] + min({up, leftDiag, rightDiag});
            }
            previous = current;
        }
        return *min_element(previous.begin(), previous.end());
    }

    // 7. Ninja and his Friends / Cherry Pickup II.
    // Two robots start at top-left and top-right; each moves -1, 0, or +1 column per row.
    // Brute: O(9^rows), stack O(rows). Memo: O(rows*cols^2) time and memory.
    // Tabulation: O(rows*cols^2) time and memory. Space optimized: O(cols^2) memory.
    static long long friendsBrute(const vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        return friendsBruteHelper(grid, 0, 0, (int)grid[0].size() - 1);
    }

    static long long friendsMemoization(const vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<vector<long long>>> memo(
            rows, vector<vector<long long>>(cols, vector<long long>(cols, LLONG_MIN)));
        return friendsMemoHelper(grid, 0, 0, cols - 1, memo);
    }

    static long long friendsTabulation(const vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<vector<long long>>> dp(
            rows, vector<vector<long long>>(cols, vector<long long>(cols, NEG)));

        for (int c1 = 0; c1 < cols; c1++) {
            for (int c2 = 0; c2 < cols; c2++) {
                dp[rows - 1][c1][c2] = grid[rows - 1][c1];
                if (c1 != c2) dp[rows - 1][c1][c2] += grid[rows - 1][c2];
            }
        }

        for (int r = rows - 2; r >= 0; r--) {
            for (int c1 = 0; c1 < cols; c1++) {
                for (int c2 = 0; c2 < cols; c2++) {
                    long long current = grid[r][c1];
                    if (c1 != c2) current += grid[r][c2];
                    long long best = NEG;

                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int n1 = c1 + d1, n2 = c2 + d2;
                            if (n1 >= 0 && n1 < cols && n2 >= 0 && n2 < cols)
                                best = max(best, dp[r + 1][n1][n2]);
                        }
                    }
                    dp[r][c1][c2] = current + best;
                }
            }
        }
        return dp[0][0][cols - 1];
    }

    static long long friendsOptimal(const vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<long long>> next(cols, vector<long long>(cols, NEG));

        for (int c1 = 0; c1 < cols; c1++) {
            for (int c2 = 0; c2 < cols; c2++) {
                next[c1][c2] = grid[rows - 1][c1];
                if (c1 != c2) next[c1][c2] += grid[rows - 1][c2];
            }
        }

        for (int r = rows - 2; r >= 0; r--) {
            vector<vector<long long>> currentDP(cols, vector<long long>(cols, NEG));
            for (int c1 = 0; c1 < cols; c1++) {
                for (int c2 = 0; c2 < cols; c2++) {
                    long long current = grid[r][c1];
                    if (c1 != c2) current += grid[r][c2];
                    long long best = NEG;

                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int n1 = c1 + d1, n2 = c2 + d2;
                            if (n1 >= 0 && n1 < cols && n2 >= 0 && n2 < cols)
                                best = max(best, next[n1][n2]);
                        }
                    }
                    currentDP[c1][c2] = current + best;
                }
            }
            next = currentDP;
        }
        return next[0][cols - 1];
    }
};

int main() {
    cout << "NINJA'S TRAINING\n";
    vector<vector<int>> training = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    cout << "Brute: " << GridDP::trainingBrute(training) << '\n';
    cout << "Memoization: " << GridDP::trainingMemoization(training) << '\n';
    cout << "Tabulation: " << GridDP::trainingTabulation(training) << '\n';
    cout << "Optimal: " << GridDP::trainingOptimal(training) << "\n\n";

    cout << "UNIQUE PATHS (3 x 3)\n";
    cout << "Brute: " << GridDP::uniquePathsBrute(3, 3) << '\n';
    cout << "Memoization: " << GridDP::uniquePathsMemoization(3, 3) << '\n';
    cout << "Tabulation: " << GridDP::uniquePathsTabulation(3, 3) << '\n';
    cout << "Optimal: " << GridDP::uniquePathsOptimal(3, 3) << "\n\n";

    cout << "UNIQUE PATHS II\n";
    vector<vector<int>> obstacles = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << "Brute: " << GridDP::uniquePathsWithObstaclesBrute(obstacles) << '\n';
    cout << "Memoization: " << GridDP::uniquePathsWithObstaclesMemoization(obstacles) << '\n';
    cout << "Tabulation: " << GridDP::uniquePathsWithObstaclesTabulation(obstacles) << '\n';
    cout << "Optimal: " << GridDP::uniquePathsWithObstaclesOptimal(obstacles) << "\n\n";

    cout << "MINIMUM PATH SUM\n";
    vector<vector<int>> costs = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << "Brute: " << GridDP::minPathSumBrute(costs) << '\n';
    cout << "Memoization: " << GridDP::minPathSumMemoization(costs) << '\n';
    cout << "Tabulation: " << GridDP::minPathSumTabulation(costs) << '\n';
    cout << "Optimal: " << GridDP::minPathSumOptimal(costs) << "\n\n";

    cout << "TRIANGLE MINIMUM PATH SUM\n";
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << "Brute: " << GridDP::triangleBrute(triangle) << '\n';
    cout << "Memoization: " << GridDP::triangleMemoization(triangle) << '\n';
    cout << "Tabulation: " << GridDP::triangleTabulation(triangle) << '\n';
    cout << "Optimal: " << GridDP::triangleOptimal(triangle) << "\n\n";

    cout << "MINIMUM FALLING PATH SUM\n";
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << "Brute: " << GridDP::fallingPathBrute(matrix) << '\n';
    cout << "Memoization: " << GridDP::fallingPathMemoization(matrix) << '\n';
    cout << "Tabulation: " << GridDP::fallingPathTabulation(matrix) << '\n';
    cout << "Optimal: " << GridDP::fallingPathOptimal(matrix) << "\n\n";

    cout << "NINJA AND HIS FRIENDS\n";
    vector<vector<int>> cherries = {{2, 3, 1, 2}, {3, 4, 2, 2},
                                    {5, 6, 3, 5}};
    cout << "Brute: " << GridDP::friendsBrute(cherries) << '\n';
    cout << "Memoization: " << GridDP::friendsMemoization(cherries) << '\n';
    cout << "Tabulation: " << GridDP::friendsTabulation(cherries) << '\n';
    cout << "Optimal: " << GridDP::friendsOptimal(cherries) << '\n';

    return 0;
}
