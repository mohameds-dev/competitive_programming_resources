#include <bits/stdc++.h>
using namespace std;

// --- Your "edge" struct (assuming you have this) ---
struct edge {
    int from, to, distance;
};

// --- ICPC-Style Floyd-Warshall Library Code ---

// !! Change this based on problem constraints !!
const int MAXN = 103; // Max number of nodes + 1 (for 1-indexing)
using ll = long long;
const ll INF = 1e18;

struct FloydWarshall {
    ll dp[MAXN][MAXN];
    int next_hop[MAXN][MAXN];
    int N; // Actual number of nodes

    // Initialize for 'n' nodes (1-indexed)
    FloydWarshall(int nodes) {
        N = nodes;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dp[i][j] = (i == j) ? 0 : INF;
                next_hop[i][j] = -1; // -1 means no path
            }
            next_hop[i][i] = i;
        }
    }

    // Add a directed edge
    void add_edge(int u, int v, ll w) {
        if (w < dp[u][v]) { // Handle parallel edges
            dp[u][v] = w;
            next_hop[u][v] = v; // The first hop from u to v is v
        }
    }

    // Run the O(N^3) algorithm
    void run() {
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    // Check for INF to prevent overflow
                    if (dp[i][k] == INF || dp[k][j] == INF) continue;

                    ll new_dist = dp[i][k] + dp[k][j];
                    if (new_dist < dp[i][j]) {
                        dp[i][j] = new_dist;
                        // The first hop from i->j is the same as the first hop from i->k
                        next_hop[i][j] = next_hop[i][k];
                    }
                }
            }
        }
    }

    // Get the shortest path distance from u to v
    ll get_dist(int u, int v) {
        return dp[u][v]; // Will be INF if no path
    }

    // Reconstruct the path from u to v
    vector<int> get_path(int u, int v) {
        if (dp[u][v] == INF) {
            return {}; // No path
        }
        
        vector<int> path;
        int curr = u;
        while (curr != v) {
            if (curr == -1) return {}; // Should not happen if dp[u][v] != INF
            path.push_back(curr);
            curr = next_hop[curr][v];
        }
        path.push_back(v);
        return path;
    }

    // Check for negative cycles
    bool has_negative_cycle() {
        for (int i = 1; i <= N; i++) {
            if (dp[i][i] < 0) {
                return true;
            }
        }
        return false;
    }
};