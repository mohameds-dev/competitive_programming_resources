#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.hpp"
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

