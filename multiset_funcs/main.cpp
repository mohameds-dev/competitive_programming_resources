#include <bits/stdc++.h>
using namespace std;

// Descending comparator
struct Descending {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main() {
    vector<int> values = {15, 3, 22, 11, 5, 18, 7};

    multiset<int, Descending> ms_desc(values.begin(), values.end());

    cout << "Descending: ";
    for (int x : ms_desc) cout << x << " ";
    cout << "\n";

    int target = 11;
    auto lb = ms_desc.lower_bound(target); // first element >= target according to Descending
    auto ub = ms_desc.upper_bound(target); // first element > target according to Descending
    cout << "lower_bound(" << target << ") = " << *lb
         << ", upper_bound(" << target << ") = " << *ub << "\n";

    return 0;
}
