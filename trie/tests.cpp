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

TEST_CASE("Trie insert and count empty string", "[trie]") {
    root = new Node();
    insert("");
    REQUIRE(count("") == 0);
}

TEST_CASE("Trie insert and count non-existent string", "[trie]") {
    root = new Node();
    insert("hello");
    REQUIRE(count("world") == 0);
}

TEST_CASE("Trie insert and count", "[trie]") {
    root = new Node();
    insert("hello");
    insert("world");
    REQUIRE(count("hello") == 1);
    REQUIRE(count("world") == 1);
    REQUIRE(count("hell") == 1);
    REQUIRE(count("wor") == 1);
}

TEST_CASE("Trie insert and count common prefix", "[trie]") {
    root = new Node();
    insert("hello");
    insert("hell");
    insert("helipad");
    REQUIRE(count("hello") == 1);
    REQUIRE(count("hell") == 2);
    REQUIRE(count("hel") == 3);
}
