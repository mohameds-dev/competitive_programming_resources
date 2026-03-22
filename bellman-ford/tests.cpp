#define CATCH_CONFIG_MAIN
#include "../utils/catch2.hpp"
#include "code.cpp"

TEST_CASE("Bellman-Ford basic shortest paths", "[bellman]") {
    n = 5;
    vector<edge> edges = {
        {1, 2, 6}, {1, 3, 7}, {2, 3, 8}, {2, 4, 5}, {2, 5, -4},
        {3, 4, -3}, {3, 5, 9}, {4, 2, -2}, {5, 4, 7}
    };

    bool hasNegCycle = bellmanFord(1, 4, edges);
    REQUIRE(hasNegCycle == false);
}

TEST_CASE("Bellman-Ford detects negative cycle", "[bellman-neg]") {
    n = 3;
    vector<edge> edges = {
        {1, 2, 4}, {2, 3, -10}, {3, 1, 3}
    };

    bool hasNegCycle = bellmanFord(1, 3, edges);
    REQUIRE(hasNegCycle == true);
}
