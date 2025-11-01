#include <bits/stdc++.h>
using namespace std;

void test_assert(bool condition, const string &message = "") {
    if (!condition) {
        throw runtime_error("Assertion failed: " + message);
    }
}