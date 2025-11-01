#include <bits/stdc++.h>
using namespace std;
#include "code.hpp"
#include "../utils/test_assert.hpp"

// Canary test to verify testing framework works
void test_canary() {
    test_assert(1 + 1 == 2, "1 + 1 should equal 2");
}

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

void test_segment_tree_gives_correct_sum() {
    segment_tree<int> st = build_segment_tree_with_numbers(6);
    test_assert(st.get(0, 1).val == 1);
    test_assert(st.get(0, 2).val == 3);
    test_assert(st.get(0, 3).val == 6);
    test_assert(st.get(0, 4).val == 10);
    test_assert(st.get(0, 5).val == 15);
    test_assert(st.get(0, 6).val == 21);
}

void test_segment_tree_gives_correct_merge_sum_result() {
    segment_tree<int> st = build_segment_tree_with_numbers(6);
    test_assert(st.merge(st.get(0, 1), st.get(1, 2)).val == 3);
}

// STEP 1: Add subject-specific tests below
// Example:
// void test_example() {
//     // Test implementation using test_assert (throws exceptions instead of aborting)
//     test_assert(condition, "descriptive error message");
//     cout << "Example test passed!" << endl;
// }

 // STEP 2: Add more tests here
vector<function<void()>> tests_arr = {
    test_canary,
    test_segment_tree_gives_correct_sum,
    test_segment_tree_gives_correct_merge_sum_result,
};

// main() is not to be modified
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int passed_count = 0;
    for (auto test : tests_arr) {
        try {
            test();
            passed_count++;
        } catch (const exception &e) {
            cout << "Test failed: " << e.what() << endl;
        } catch (...) {
            cout << "Test failed with unknown error" << endl;
        }
    }
    cout << passed_count << "/" << tests_arr.size() << " tests passed." << endl;
    return 0;
}

