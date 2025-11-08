#include <bits/stdc++.h>
using namespace std;

// Default (ascending) multiset behavior
void multiset_default() {
    vector<int> values = {15, 3, 22, 11, 5, 18, 7};

    multiset<int> ms(values.begin(), values.end());
    // ms = {3, 5, 7, 11, 15, 18, 22}

    ms.insert(11); // duplicates allowed
    // ms = {3, 5, 7, 11, 11, 15, 18, 22}

    ms.count(11); // 2
    ms.find(11);  // points to first 11
    ms.erase(11); // removes all 11s by default
    // ms = {3, 5, 7, 15, 18, 22}

    auto lb = ms.lower_bound(11); // first element >= 11 -> 15
    auto ub = ms.upper_bound(11); // first element > 11 -> 15

    // Iteration is in ascending order
    // elements printed: 3 5 7 15 18 22
}

// Descending comparator (equivalent to greater<int>)
struct Descending {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

void multiset_descending() {
    vector<int> values = {15, 3, 22, 11, 5, 18, 7};

    // equivalent: multiset<int, greater<int>> ms_desc;
    multiset<int, Descending> ms_desc(values.begin(), values.end());
    // ms_desc = {22, 18, 15, 11, 7, 5, 3}

    ms_desc.insert(11); // duplicates allowed
    // ms_desc = {22, 18, 15, 11, 11, 7, 5, 3}

    int target = 11;
    auto lb = ms_desc.lower_bound(target);
    // lower_bound(11) = first element 'x' such that !(x > 11) (i.e., x <= 11) -> 11 (first one)
    auto ub = ms_desc.upper_bound(target);
    // upper_bound(11) = first element 'x' such that !(x >= 11) (i.e., x < 11) (in descending order) -> 7

    // Iteration is in descending order
    // elements printed: 22 18 15 11 11 7 5 3
}
