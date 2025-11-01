#include <bits/stdc++.h>
using namespace std;
#include "code.hpp"
#include "../utils/test_assert.hpp"

// Canary test to verify testing framework works
void test_canary() {
    test_assert(1 + 1 == 2, "1 + 1 should equal 2");
}

// STEP 1: Add subject-specific tests below
// Example:
// void test_example() {
//     // Test implementation using code from code.hpp
//     // Use test_assert instead of assert so failures can be caught
//     test_assert(condition, "descriptive error message");
//     cout << "Example test passed!" << endl;
// }


// STEP 2: Add more tests here
vector<function<void()>> tests_arr = {
    test_canary,
    // test_example,
};

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

