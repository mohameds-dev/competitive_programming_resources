#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#include "../utils/catch2.hpp"

template <typename T>
vector<T> to_vector(const multiset<T>& ms) {
    return vector<T>(ms.begin(), ms.end());
}

template <typename T, typename Compare>
vector<T> to_vector(const multiset<T, Compare>& ms) {
    return vector<T>(ms.begin(), ms.end());
}

TEST_CASE("Multiset ascending and descending", "[multiset]") {
    vector<int> values = {15, 3, 22, 11, 5, 18, 7};

    SECTION("Ascending multiset") {
        multiset<int> ms(values.begin(), values.end());
        REQUIRE(to_vector(ms) == vector<int>{3,5,7,11,15,18,22});

        auto lb = ms.lower_bound(11); // first >= 11
        auto ub = ms.upper_bound(11); // first > 11
        REQUIRE(*lb == 11);
        REQUIRE(*ub == 15);
    }

    SECTION("Descending multiset using greater<>") {
        multiset<int, greater<int>> ms_desc(values.begin(), values.end());
        REQUIRE(to_vector(ms_desc) == vector<int>{22,18,15,11,7,5,3});

        auto lb = ms_desc.lower_bound(11); // first >= 11 according to greater<> → first ≤ 11 normally
        auto ub = ms_desc.upper_bound(11); // first > 11 according to greater<> → first < 11 normally
        REQUIRE(*lb == 11);
        REQUIRE(*ub == 7);
    }

    SECTION("Descending multiset custom struct") {
        struct Descending {
            bool operator()(int a, int b) const { return a > b; }
        };
        multiset<int, Descending> ms_desc2(values.begin(), values.end());
        REQUIRE(to_vector(ms_desc2) == vector<int>{22,18,15,11,7,5,3});
    }
}