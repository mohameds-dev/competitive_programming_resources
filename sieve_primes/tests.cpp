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

TEST_CASE("Prime sieve basic tests", "[sieve]") {
    sieve(20);
    vector<int> expected = {2,3,5,7,11,13,17,19};
    for (int i = 0; i < 20; i++) {
        bool is_expected = find(expected.begin(), expected.end(), i) != expected.end();
        REQUIRE(prime[i] == is_expected);
    }
}