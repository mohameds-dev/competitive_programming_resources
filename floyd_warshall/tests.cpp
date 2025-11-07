#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#include "../utils/catch2.hpp"

// STEP 1: Add subject-specific tests below
// Example:
// TEST_CASE("Test description", "[tag]") {
//     REQUIRE(condition);  // Fails fast on failure
//     CHECK(another_condition);  // Continues on failure
// }

// Make sure the FloydWarshall struct, MAXN, ll, and INF
// are defined or included above this line.
// --- (Your FloydWarshall struct code goes here) ---


TEST_CASE("Floyd-Warshall", "[floyd_warshall]") {

    // This graph will be used for several sections
    // 4 nodes
    // 1 -> 2 (cost 3)
    // 2 -> 3 (cost 4)
    // 1 -> 3 (cost 10, this is the expensive "trap" path)
    // 3 -> 4 (cost 2)
    FloydWarshall fw(4);
    fw.add_edge(1, 2, 3);
    fw.add_edge(2, 3, 4);
    fw.add_edge(1, 3, 10);
    fw.add_edge(3, 4, 2);
    fw.run();

    SECTION("Basic Pathfinding") {
        // Path 1->2->3 should be 3 + 4 = 7
        // This is cheaper than the direct 1->3 edge (cost 10)
        REQUIRE(fw.get_dist(1, 3) == 7);
        
        // Path 1->2->3->4 should be 7 + 2 = 9
        REQUIRE(fw.get_dist(1, 4) == 9);
        
        // Path 2->3->4
        REQUIRE(fw.get_dist(2, 4) == 6);
        
        // Simple direct edge
        REQUIRE(fw.get_dist(1, 2) == 3);
    }

    SECTION("No Path") {
        // This graph is a Directed Acyclic Graph (DAG)
        // There should be no path backwards.
        REQUIRE(fw.get_dist(4, 1) == INF);
        REQUIRE(fw.get_dist(3, 1) == INF);
        REQUIRE(fw.get_dist(2, 1) == INF);
    }

    SECTION("Self-Loops") {
        // Distance to self should always be 0
        REQUIRE(fw.get_dist(1, 1) == 0);
        REQUIRE(fw.get_dist(2, 2) == 0);
        REQUIRE(fw.get_dist(3, 3) == 0);
        REQUIRE(fw.get_dist(4, 4) == 0);
    }

    SECTION("Path Reconstruction") {
        // Path 1->4 should be {1, 2, 3, 4}
        vector<int> path1_4 = fw.get_path(1, 4);
        vector<int> expected1_4 = {1, 2, 3, 4};
        REQUIRE(path1_4 == expected1_4);

        // Path 1->3 should be {1, 2, 3}
        vector<int> path1_3 = fw.get_path(1, 3);
        vector<int> expected1_3 = {1, 2, 3};
        REQUIRE(path1_3 == expected1_3);

        // Path 1->2 is a direct edge
        vector<int> path1_2 = fw.get_path(1, 2);
        vector<int> expected1_2 = {1, 2};
        REQUIRE(path1_2 == expected1_2);

        // Path 4->1 should be empty
        vector<int> path4_1 = fw.get_path(4, 1);
        REQUIRE(path4_1.empty());
    }

    SECTION("Parallel Edges") {
        // Tests if add_edge correctly handles multiple edges
        FloydWarshall fw_para(3);
        fw_para.add_edge(1, 2, 100);
        fw_para.add_edge(1, 2, 50); // This one is cheaper
        fw_para.add_edge(1, 2, 75);
        fw_para.run();

        REQUIRE(fw_para.get_dist(1, 2) == 50);
    }

    SECTION("Negative Edges (No Cycle)") {
        FloydWarshall fw_neg(3);
        fw_neg.add_edge(1, 2, 5);
        fw_neg.add_edge(2, 3, 5);
        fw_neg.add_edge(1, 3, -3); // Negative shortcut
        fw_neg.run();

        REQUIRE(fw_neg.has_negative_cycle() == false);
        REQUIRE(fw_neg.get_dist(1, 3) == -3);
        REQUIRE(fw_neg.get_dist(1, 2) == 5); // 1->2 is still 5
    }

    SECTION("Negative Cycle Detection") {
        FloydWarshall fw_cycle(3);
        fw_cycle.add_edge(1, 2, 2);
        fw_cycle.add_edge(2, 3, 2);
        fw_cycle.add_edge(3, 1, -5); // Total cycle cost: 2+2-5 = -1
        fw_cycle.run();

        // Check the public-facing function
        REQUIRE(fw_cycle.has_negative_cycle() == true);

        // Internally, a node's distance to itself should be < 0
        REQUIRE(fw_cycle.get_dist(1, 1) < 0);
        REQUIRE(fw_cycle.get_dist(2, 2) < 0);
        REQUIRE(fw_cycle.get_dist(3, 3) < 0);
    }
}
