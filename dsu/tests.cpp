#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#include "../utils/catch2.hpp"

TEST_CASE("DSU Initialization", "[dsu]") {
    DSU dsu(10);
    REQUIRE(dsu.parent.size() == 10);
    REQUIRE(dsu.comp_size.size() == 10);

    // Test initial state: all elements are separate
    for (int i = 0; i < 10; ++i) {
        REQUIRE(dsu.find(i) == i);  // Each is its own parent
        REQUIRE(dsu.size(i) == 1);  // Each component size is 1
        if (i > 0) {
            REQUIRE_FALSE(dsu.same(i, i - 1)); // Not connected
        }
    }
}

TEST_CASE("DSU Basic Union and Find", "[dsu]") {
    DSU dsu(10);
    
    // Test unite return value
    REQUIRE(dsu.unite(1, 2));   // First union should return true
    REQUIRE(dsu.same(1, 2));    // Now they are in the same set
    
    // Test find (path compression not fully tested here, but root finding is)
    REQUIRE(dsu.find(1) == dsu.find(2));
    REQUIRE_FALSE(dsu.same(1, 3)); // Check against other sets

    // Test redundant union
    REQUIRE_FALSE(dsu.unite(1, 2)); // Should return false
    REQUIRE_FALSE(dsu.unite(2, 1)); // Should return false
}

TEST_CASE("DSU Component Size Tracking", "[dsu]") {
    DSU dsu(10);

    dsu.unite(0, 1);
    REQUIRE(dsu.size(0) == 2);
    REQUIRE(dsu.size(1) == 2);
    REQUIRE(dsu.size(2) == 1); // Other components unaffected

    dsu.unite(2, 3);
    REQUIRE(dsu.size(2) == 2);
    REQUIRE(dsu.size(3) == 2);
    
    // Test merging two components
    dsu.unite(0, 2);
    REQUIRE(dsu.size(0) == 4); // size = 4
    REQUIRE(dsu.size(1) == 4);
    REQUIRE(dsu.size(2) == 4);
    REQUIRE(dsu.size(3) == 4);
    REQUIRE(dsu.size(4) == 1); // Unaffected
}

TEST_CASE("DSU Union by Size", "[dsu]") {
    DSU dsu(10);

    // Create a large component (0, 1, 2, 3)
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(0, 2); // size = 4
    int root_large = dsu.find(0);
    REQUIRE(dsu.size(root_large) == 4);

    // Create a small component (4, 5)
    dsu.unite(4, 5); // size = 2
    int root_small = dsu.find(4);
    REQUIRE(dsu.size(root_small) == 2);

    // Merge small into large
    dsu.unite(root_large, root_small);
    
    // The new root should be the original large root
    REQUIRE(dsu.find(0) == root_large);
    REQUIRE(dsu.find(4) == root_large);
    REQUIRE(dsu.parent[root_small] == root_large); // Check parent directly
    REQUIRE(dsu.size(0) == 6);
}

TEST_CASE("DSU Path Compression", "[dsu]") {
    DSU dsu(10);

    // Create a chain: 0-1, 1-2, 2-3
    // With union-by-size, this will be:
    // unite(0, 1) -> parent[1] = 0, comp_size[0] = 2
    // unite(2, 3) -> parent[3] = 2, comp_size[2] = 2
    // unite(0, 2) -> parent[2] = 0, comp_size[0] = 4
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(0, 2);
    
    // At this point, we have:
    // parent[1] = 0
    // parent[3] = 2
    // parent[2] = 0
    // parent[0] = 0

    // Now, find(3). The path is 3 -> 2 -> 0.
    REQUIRE(dsu.parent[3] == 2); // Before find
    REQUIRE(dsu.parent[2] == 0);
    REQUIRE(dsu.find(3) == 0); // find(3) returns root 0

    // After find(3), path compression should set parent[3] directly to 0.
    REQUIRE(dsu.parent[3] == 0);
}