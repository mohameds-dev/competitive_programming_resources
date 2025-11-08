#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, m; // number of nodes and edges

struct edge {
    int a, b, w;
};

// Bellman-Ford algorithm
// Time: O(N * M)   | Space: O(N)
// Returns true if a negative cycle exists, false otherwise.
bool bellmanFord(int start, int dest, vector<edge> &edges) {
    int d[N];
    memset(d, 0x3f, sizeof d); // initialize distances to "infinity"
    d[start] = 0;

    // Relax edges (n-1) times
    for (int i = 0; i < n - 1; ++i) {
        for (auto &e : edges) {
            if (d[e.a] < 1e9 && d[e.b] > d[e.a] + e.w)
                d[e.b] = d[e.a] + e.w;
        }
    }

    // One more pass for negative cycle detection
    for (auto &e : edges) {
        if (d[e.a] < 1e9 && d[e.b] > d[e.a] + e.w)
            return true; // negative cycle found
    }

    // Optional: print distance to dest (if reachable)
    if (d[dest] < 1e9)
        cout << "Shortest distance to " << dest << ": " << d[dest] << "\n";
    else
        cout << "Destination unreachable.\n";

    return false;
}
