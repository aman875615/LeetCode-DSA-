#include <bits/stdc++.h>
using namespace std;

class GraphAlgorithms {
public:
    // 1. Detect a cycle in an undirected graph.
    // edges contains {u, v}; vertices are 0..V-1.
    static bool hasUndirectedCycle(int V, const vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> visited(V, 0);
        for (int start = 0; start < V; start++) {
            if (visited[start]) continue;

            queue<pair<int, int>> q;
            q.push({start, -1});
            visited[start] = 1;

            while (!q.empty()) {
                auto [node, parent] = q.front();
                q.pop();

                for (int next : adj[node]) {
                    if (!visited[next]) {
                        visited[next] = 1;
                        q.push({next, node});
                    } else if (next != parent) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // 2. Check whether an undirected graph is bipartite.
    static bool isBipartite(const vector<vector<int>>& adj) {
        int V = adj.size();
        vector<int> color(V, -1);

        for (int start = 0; start < V; start++) {
            if (color[start] != -1) continue;

            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int next : adj[node]) {
                    if (color[next] == -1) {
                        color[next] = 1 - color[node];
                        q.push(next);
                    } else if (color[next] == color[node]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    // 3. Topological sort using Kahn's algorithm.
    // For a directed acyclic graph, returns a topological ordering.
    // If a cycle exists, returns an empty vector.
    static vector<int> topologicalSort(int V, const vector<vector<int>>& adj) {
        vector<int> indegree(V, 0);
        for (int node = 0; node < V; node++) {
            for (int next : adj[node]) indegree[next]++;
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            for (int next : adj[node]) {
                indegree[next]--;
                if (indegree[next] == 0) q.push(next);
            }
        }

        if ((int)order.size() != V) return {};
        return order;
    }

    // 4. Detect a cycle in a directed graph with Kahn's algorithm.
    static bool hasDirectedCycle(int V, const vector<vector<int>>& adj) {
        return (int)topologicalSort(V, adj).size() != V;
    }

    // 5. Dijkstra: shortest distances from source.
    // Weighted adjacency list: adj[u] contains {v, weight}.
    // All edge weights must be non-negative.
    static vector<long long> dijkstra(
        int V, const vector<vector<pair<int, int>>>& adj, int source) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> dist(V, INF);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [distance, node] = pq.top();
            pq.pop();

            if (distance != dist[node]) continue;

            for (auto [next, weight] : adj[node]) {
                if (dist[next] > distance + weight) {
                    dist[next] = distance + weight;
                    pq.push({dist[next], next});
                }
            }
        }
        return dist;
    }

    // 6. Dijkstra plus parent tracking: shortest path source -> destination.
    // Returns an empty vector if destination cannot be reached.
    static vector<int> shortestPath(
        int V, const vector<vector<pair<int, int>>>& adj,
        int source, int destination) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> dist(V, INF);
        vector<int> parent(V, -1);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [distance, node] = pq.top();
            pq.pop();
            if (distance != dist[node]) continue;

            for (auto [next, weight] : adj[node]) {
                if (dist[next] > distance + weight) {
                    dist[next] = distance + weight;
                    parent[next] = node;
                    pq.push({dist[next], next});
                }
            }
        }

        if (dist[destination] == INF) return {};

        vector<int> path;
        for (int node = destination; node != -1; node = parent[node]) {
            path.push_back(node);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // 7. Shortest distance in a binary maze; 1=open, 0=blocked.
    // Source and destination are {row, column}; returns -1 if unreachable.
    static int shortestDistanceBinaryMaze(
        const vector<vector<int>>& grid,
        pair<int, int> source, pair<int, int> destination) {
        int rows = grid.size();
        if (rows == 0) return -1;
        int cols = grid[0].size();

        int sr = source.first, sc = source.second;
        int tr = destination.first, tc = destination.second;
        if (sr < 0 || sr >= rows || sc < 0 || sc >= cols ||
            tr < 0 || tr >= rows || tc < 0 || tc >= cols ||
            grid[sr][sc] == 0 || grid[tr][tc] == 0) {
            return -1;
        }

        vector<vector<int>> dist(rows, vector<int>(cols, -1));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        dist[sr][sc] = 0;
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (r == tr && c == tc) return dist[r][c];

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                    grid[nr][nc] == 1 && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        return -1;
    }

    // 8. Path with minimum effort (minimum possible maximum height difference).
    static int minimumEffortPath(const vector<vector<int>>& heights) {
        int rows = heights.size();
        if (rows == 0) return 0;
        int cols = heights[0].size();

        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
        priority_queue<tuple<int, int, int>,
                       vector<tuple<int, int, int>>,
                       greater<tuple<int, int, int>>> pq;
        effort[0][0] = 0;
        pq.push({0, 0, 0});
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [currentEffort, r, c] = pq.top();
            pq.pop();
            if (r == rows - 1 && c == cols - 1) return currentEffort;
            if (currentEffort != effort[r][c]) continue;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

                int step = abs(heights[r][c] - heights[nr][nc]);
                int candidate = max(currentEffort, step);
                if (candidate < effort[nr][nc]) {
                    effort[nr][nc] = candidate;
                    pq.push({candidate, nr, nc});
                }
            }
        }
        return 0;
    }

    // 9. Cheapest flight with at most K stops.
    // flights entries are {from, to, price}; returns -1 if unreachable.
    static int cheapestFlight(int n, const vector<vector<int>>& flights,
                              int source, int destination, int K) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> cost(n, INF);
        cost[source] = 0;

        // At most K stops means at most K+1 edges.
        for (int edgesUsed = 1; edgesUsed <= K + 1; edgesUsed++) {
            vector<long long> nextCost = cost;
            for (const auto& flight : flights) {
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];
                if (cost[from] != INF) {
                    nextCost[to] = min(nextCost[to], cost[from] + price);
                }
            }
            cost.swap(nextCost);
        }

        return cost[destination] == INF ? -1 : (int)cost[destination];
    }

    // 10. Minimum multiplications to reach end; arithmetic is modulo 100000.
    static int minimumMultiplications(const vector<int>& multipliers,
                                      int start, int end) {
        const int MOD = 100000;
        vector<int> dist(MOD, INT_MAX);
        queue<int> q;
        start %= MOD;
        end %= MOD;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int value = q.front();
            q.pop();
            if (value == end) return dist[value];

            for (int factor : multipliers) {
                int next = (int)((1LL * value * factor) % MOD);
                if (dist[next] == INT_MAX) {
                    dist[next] = dist[value] + 1;
                    q.push(next);
                }
            }
        }
        return -1;
    }

    // 11. Number of shortest ways to reach destination.
    // roads entries are {u, v, travelTime}; graph is undirected.
    static int countShortestWays(int n, const vector<vector<int>>& roads) {
        const long long MOD = 1'000'000'007;
        const long long INF = LLONG_MAX / 4;
        vector<vector<pair<int, int>>> adj(n);

        for (const auto& road : roads) {
            int u = road[0], v = road[1], time = road[2];
            adj[u].push_back({v, time});
            adj[v].push_back({u, time});
        }

        vector<long long> dist(n, INF), ways(n, 0);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;
        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [distance, node] = pq.top();
            pq.pop();
            if (distance != dist[node]) continue;

            for (auto [next, time] : adj[node]) {
                long long candidate = distance + time;
                if (candidate < dist[next]) {
                    dist[next] = candidate;
                    ways[next] = ways[node];
                    pq.push({candidate, next});
                } else if (candidate == dist[next]) {
                    ways[next] = (ways[next] + ways[node]) % MOD;
                }
            }
        }
        return (int)ways[n - 1];
    }
};

int main() {
    // Sample 1: cycle in undirected graph
    vector<vector<int>> undirectedEdges = {{0, 1}, {1, 2}, {2, 0}};
    cout << boolalpha;
    cout << "Undirected graph has cycle: "
         << GraphAlgorithms::hasUndirectedCycle(3, undirectedEdges) << '\n';

    // Sample 2: bipartite graph
    vector<vector<int>> bipartiteAdj = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Graph is bipartite: "
         << GraphAlgorithms::isBipartite(bipartiteAdj) << '\n';

    // Sample 3: topological sort and directed cycle check
    vector<vector<int>> directedAdj = {{1, 2}, {3}, {3}, {}};
    vector<int> order = GraphAlgorithms::topologicalSort(4, directedAdj);
    cout << "Topological order: ";
    for (int node : order) cout << node << ' ';
    cout << "\nDirected graph has cycle: "
         << GraphAlgorithms::hasDirectedCycle(4, directedAdj) << '\n';

    // Sample 4: Dijkstra and print shortest path
    vector<vector<pair<int, int>>> weightedAdj(4);
    auto addEdge = [&](int u, int v, int w) {
        weightedAdj[u].push_back({v, w});
        weightedAdj[v].push_back({u, w});
    };
    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(2, 1, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);

    vector<long long> distances = GraphAlgorithms::dijkstra(4, weightedAdj, 0);
    cout << "Dijkstra distances from 0: ";
    for (long long d : distances) cout << d << ' ';
    cout << '\n';

    vector<int> path = GraphAlgorithms::shortestPath(4, weightedAdj, 0, 3);
    cout << "Shortest path 0 to 3: ";
    for (int node : path) cout << node << ' ';
    cout << '\n';

    // Sample 5: shortest path in binary maze
    vector<vector<int>> maze = {{1, 1, 1}, {0, 1, 0}, {1, 1, 1}};
    cout << "Binary maze distance: "
         << GraphAlgorithms::shortestDistanceBinaryMaze(maze, {0, 0}, {2, 2}) << '\n';

    // Sample 6: minimum effort path
    vector<vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    cout << "Minimum effort: "
         << GraphAlgorithms::minimumEffortPath(heights) << '\n';

    // Sample 7: cheapest flight with at most K stops
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    cout << "Cheapest flight: "
         << GraphAlgorithms::cheapestFlight(3, flights, 0, 2, 1) << '\n';

    // Sample 8: minimum multiplications
    vector<int> multipliers = {2, 5, 7};
    cout << "Minimum multiplications: "
         << GraphAlgorithms::minimumMultiplications(multipliers, 3, 30) << '\n';

    // Sample 9: number of shortest ways
    vector<vector<int>> roads = {
        {0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3},
        {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1},
        {0, 4, 5}, {4, 6, 2}
    };
    cout << "Number of shortest ways: "
         << GraphAlgorithms::countShortestWays(7, roads) << '\n';

    return 0;
}
