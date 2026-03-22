#define CATCH_CONFIG_MAIN
#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#include "../utils/catch2.hpp"

segment_tree<int> build_segment_tree_with_numbers(int num_leaves) {
    segment_tree<int> st;
    st.init(num_leaves);
    vector<int> v(num_leaves);
    for (int i = 0; i < num_leaves; i++) {
        v[i] = i + 1;
    }
    st.build(v);
    return st;
}

TEST_CASE("Canary test", "[canary]") {
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Segment tree gives correct sum", "[segment_tree]") {
    segment_tree<int> st = build_segment_tree_with_numbers(6);
    REQUIRE(st.get(0, 1).val == 1);
    REQUIRE(st.get(0, 2).val == 3);
    REQUIRE(st.get(0, 3).val == 6);
    REQUIRE(st.get(0, 4).val == 10);
    REQUIRE(st.get(0, 5).val == 15);
    REQUIRE(st.get(0, 6).val == 21);
}

TEST_CASE("Segment tree merge gives correct result", "[segment_tree]") {
    segment_tree<int> st = build_segment_tree_with_numbers(6);
    REQUIRE(st.merge(st.get(0, 1), st.get(1, 2)).val == 3);
}
