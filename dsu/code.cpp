#include <bits/stdc++.h>
using namespace std;
// All operations are amortized O(a(n)), which is nearly constant.
struct DSU {
    // parent[i] = parent of node i
    // comp_size[i] = size of component (only valid for root nodes)
    vector<int> parent, comp_size;

    // Constructor: Initializes n disjoint sets [0, n-1] - Time: O(n)
    DSU(int n) : parent(n), comp_size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    // Find: Returns the representative (root) of the set containing i
    int find(int i) {  // Time: O(a(n))
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    // Unite: Merges the sets containing i and j.
    // Returns true if a merge happened, false if already in same set.
    bool unite(int i, int j) { // Time: O(a(n))
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false; // Already united

        // Union by size
        if (comp_size[root_i] < comp_size[root_j]) swap(root_i, root_j);
        parent[root_j] = root_i;
        comp_size[root_i] += comp_size[root_j];
        return true;
    }

    // Same: Checks if i and j are in the same component.
    bool same(int i, int j) { // Time: O(a(n))
        return find(i) == find(j);
    }

    // Size: Returns the size of the component containing i.
    int size(int i) { // Time: O(a(n))
        return comp_size[find(i)];
    }
};

// O(a(n)) stands for Inverse Ackermann function, O(a(n)) stands for the Inverse Ackermann function.In simple terms, it's a function that grows incredibly slowly. It's the opposite of the Ackermann function, which is known for growing unbelievably fast.
// It is always less than 5