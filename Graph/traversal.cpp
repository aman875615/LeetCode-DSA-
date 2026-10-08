#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // Islands / enclaves ke liye DFS
    void dfsLand(int r, int c, vector<vector<int>>& grid,
                 vector<vector<int>>& vis) {
        vis[r][c] = 1;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < grid.size() &&
                nc >= 0 && nc < grid[0].size() &&
                grid[nr][nc] == 1 && !vis[nr][nc]) {
                dfsLand(nr, nc, grid, vis);
            }
        }
    }

    // Distinct islands ke shape coordinates collect karta hai
    void dfsShape(int r, int c, int baseR, int baseC,
                  vector<vector<int>>& grid,
                  vector<vector<int>>& vis,
                  vector<pair<int, int>>& shape) {
        vis[r][c] = 1;
        shape.push_back({r - baseR, c - baseC});

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < grid.size() &&
                nc >= 0 && nc < grid[0].size() &&
                grid[nr][nc] == 1 && !vis[nr][nc]) {
                dfsShape(nr, nc, baseR, baseC, grid, vis, shape);
            }
        }
    }

    // Flood fill helper
    void fillDfs(int r, int c, int oldColor, int newColor,
                 vector<vector<int>>& image) {
        image[r][c] = newColor;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < image.size() &&
                nc >= 0 && nc < image[0].size() &&
                image[nr][nc] == oldColor) {
                fillDfs(nr, nc, oldColor, newColor, image);
            }
        }
    }

    // Surrounded Regions ke liye boundary se connected O's ko mark karta hai
    void markSafe(int r, int c, vector<vector<char>>& board) {
        board[r][c] = '#';

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr >= 0 && nr < board.size() &&
                nc >= 0 && nc < board[0].size() &&
                board[nr][nc] == 'O') {
                markSafe(nr, nc, board);
            }
        }
    }

public:
    // 1. Number of Provinces
    // isConnected adjacency matrix hai.
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> vis(n, 0);
        int provinces = 0;

        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;

            provinces++;
            queue<int> q;
            q.push(i);
            vis[i] = 1;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int city = 0; city < n; city++) {
                    if (isConnected[node][city] == 1 && !vis[city]) {
                        vis[city] = 1;
                        q.push(city);
                    }
                }
            }
        }

        return provinces;
    }

    // 2. Number of Islands
    // '1' = land, '0' = water.
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;

        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int islands = 0;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == '1' && !vis[r][c]) {
                    islands++;
                    queue<pair<int, int>> q;
                    q.push({r, c});
                    vis[r][c] = 1;

                    while (!q.empty()) {
                        auto [i, j] = q.front();
                        q.pop();

                        for (int k = 0; k < 4; k++) {
                            int ni = i + dr[k];
                            int nj = j + dc[k];

                            if (ni >= 0 && ni < n &&
                                nj >= 0 && nj < m &&
                                grid[ni][nj] == '1' && !vis[ni][nj]) {
                                vis[ni][nj] = 1;
                                q.push({ni, nj});
                            }
                        }
                    }
                }
            }
        }

        return islands;
    }

    // 3. Flood Fill
    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr, int sc, int color) {
        int oldColor = image[sr][sc];

        if (oldColor == color) return image;

        fillDfs(sr, sc, oldColor, color, image);
        return image;
    }

    // 4. Number of Enclaves
    // Boundary tak pahunch sakne wale land ko pehle mark karo.
    int numberOfEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));

        for (int r = 0; r < n; r++) {
            if (grid[r][0] == 1 && !vis[r][0])
                dfsLand(r, 0, grid, vis);

            if (grid[r][m - 1] == 1 && !vis[r][m - 1])
                dfsLand(r, m - 1, grid, vis);
        }

        for (int c = 0; c < m; c++) {
            if (grid[0][c] == 1 && !vis[0][c])
                dfsLand(0, c, grid, vis);

            if (grid[n - 1][c] == 1 && !vis[n - 1][c])
                dfsLand(n - 1, c, grid, vis);
        }

        int enclaves = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 1 && !vis[r][c]) {
                    enclaves++;
                }
            }
        }

        return enclaves;
    }

    // 5. Rotten Oranges
    // 0 = empty, 1 = fresh, 2 = rotten
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }

        if (fresh == 0) return 0;

        int minutes = 0;

        while (!q.empty() && fresh > 0) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                        grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        fresh--;
                        q.push({nr, nc});
                    }
                }
            }

            minutes++;
        }

        return fresh == 0 ? minutes : -1;
    }

    // 6. Distance of Nearest Cell Having 1
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pair<int, int>> q;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                    dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }

    // 7. Surrounded Regions
    // Boundary se connected 'O' ko bachao; baaki 'O' ko 'X' karo.
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;

        int n = board.size();
        int m = board[0].size();

        for (int r = 0; r < n; r++) {
            if (board[r][0] == 'O') markSafe(r, 0, board);
            if (board[r][m - 1] == 'O') markSafe(r, m - 1, board);
        }

        for (int c = 0; c < m; c++) {
            if (board[0][c] == 'O') markSafe(0, c, board);
            if (board[n - 1][c] == 'O') markSafe(n - 1, c, board);
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (board[r][c] == 'O') board[r][c] = 'X';
                else if (board[r][c] == '#') board[r][c] = 'O';
            }
        }
    }

    // 8. Number of Distinct Islands
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> uniqueShapes;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (grid[r][c] == 1 && !vis[r][c]) {
                    vector<pair<int, int>> shape;
                    dfsShape(r, c, r, c, grid, vis, shape);
                    uniqueShapes.insert(shape);
                }
            }
        }

        return uniqueShapes.size();
    }
};