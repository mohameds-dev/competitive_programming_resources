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

TEST_CASE("Combinatorics nCr tests", "[nCr]") {
    factorials(2005);

    SECTION("Small values") {
        REQUIRE(nCr(5, 2, mod) == 10);
        REQUIRE(nCr(5, 0, mod) == 1);
        REQUIRE(nCr(5, 5, mod) == 1);
    }

    SECTION("Edge cases") {
        REQUIRE(nCr(10, -1, mod) == 0);
        REQUIRE(nCr(10, 11, mod) == 0);
    }

    SECTION("Larger values") {
        REQUIRE(nCr(1000, 500, mod) == 159835829); // precomputed mod result
    }

    SECTION("nCr symmetry") {
        REQUIRE(nCr(1234, 567, mod) == nCr(1234, 1234 - 567, mod));
    }
}


