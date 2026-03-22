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

TEST_CASE("Canary test", "[canary]") {
    REQUIRE(1 + 1 == 2);
}

void clear_graph() {
    memset(graph, 0, sizeof graph);
}

vector<tuple<int, int, int>> edges_sample_1 = {
    {1, 2, 1},
    {2, 3, 4},
    {2, 4, 1},
    {3, 4, 2},
    {3, 7, 1},
    {4, 5, 2},
    {4, 6, 6},
    {4, 7, 2},
    {5, 5, 3},
    {6, 7, 1},
};

void initialize_graph_sample_1() {
    clear_graph();
    for (auto edge : edges_sample_1) {
        int u, v, w;
        tie(u, v, w) = edge;
        graph[u].push_back({v, w});
    }
}

TEST_CASE("Dijkstra gives correct result for sample 1", "[dijkstra]") {
    initialize_graph_sample_1();
    dijkstra(1, 7);
    REQUIRE(distance_to_node[7] == 4);
    REQUIRE(parent[7] == 4);
    REQUIRE(parent[4] == 2);
    REQUIRE(parent[2] == 1);
}
