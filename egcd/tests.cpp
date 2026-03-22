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
#define ll long long

TEST_CASE("Canary test", "[canary]") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("EGCD basic tests", "[egcd]") {
    ll x, y;

    SECTION("30, 20") {
        ll g = egcd(30, 20, x, y);
        REQUIRE(g == 10);
        REQUIRE(30*x + 20*y == g);
    }

    SECTION("17, 31") {
        ll g = egcd(17, 31, x, y);
        REQUIRE(g == 1);
        REQUIRE(17*x + 31*y == g);
    }

    SECTION("101, 103") {
        ll g = egcd(101, 103, x, y);
        REQUIRE(g == 1);
        REQUIRE(101*x + 103*y == g);
    }

    SECTION("120, 23") {
        ll g = egcd(120, 23, x, y);
        REQUIRE(g == 1);
        REQUIRE(120*x + 23*y == g);
    }

    SECTION("0, 5") {
        ll g = egcd(0, 5, x, y);
        REQUIRE(g == 5);
        REQUIRE(0*x + 5*y == g);
    }

    SECTION("81, 27") {
        ll g = egcd(81, 27, x, y);
        REQUIRE(g == 27);
        REQUIRE(81*x + 27*y == g);
    }
}
