#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#include "../utils/catch2.hpp"

TEST_CASE("Hash basic functionality", "[hash]")
{
    preprocess();

    string s = "banana";
    Hash h(s);

    // Full string hash consistency
    auto fullHash = h.getHashVal();
    auto rangeHash = h.getRangeHashVal(0, s.size() - 1);
    REQUIRE(fullHash == rangeHash);

    // Substring hash equality test: "ana" occurs twice
    auto sub1 = h.getRangeHashVal(1, 3); // "ana" at index 1
    auto sub2 = h.getRangeHashVal(3, 5); // "ana" at index 3
    REQUIRE(sub1 == sub2);

    // Distinct substrings should differ
    auto diffSub = h.getRangeHashVal(0, 2); // "ban"
    REQUIRE(sub1 != diffSub);
}

TEST_CASE("Hash edge cases", "[hash-edge]")
{
    preprocess();

    // Single character test
    string s = "a";
    Hash h(s);
    REQUIRE(h.getHashVal().first > 0);
    REQUIRE(h.getHashVal().second > 0);

    // Identical strings have identical hashes
    string a = "abc", b = "abc";
    Hash ha(a), hb(b);
    REQUIRE(ha.getHashVal() == hb.getHashVal());

    // Different strings produce different hashes (almost always)
    string c = "abd";
    Hash hc(c);
    REQUIRE(ha.getHashVal() != hc.getHashVal());
}

TEST_CASE("Hash modular correctness", "[hash-mod]")
{
    preprocess();

    string s = "zzz";
    Hash h(s);
    auto val = h.getHashVal();
    REQUIRE(val.first < M);
    REQUIRE(val.second < M);
}
