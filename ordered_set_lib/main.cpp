#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// Ordered set template
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    // Initialize (O(n log n) if multiple inserts)
    ordered_set<int> os;
    os.insert(5);
    os.insert(1);
    os.insert(3);
    os.insert(7);

    // Find k-th smallest element (0-indexed) - O(log n)
    cout << *os.find_by_order(0) << " "  // 1
         << *os.find_by_order(2) << "\n"; // 5

    // Number of elements < x - O(log n)
    cout << os.order_of_key(5) << " "   // 2
         << os.order_of_key(6) << "\n"; // 3

    // Erase element - O(log n)
    os.erase(3);

    // Iterate elements - O(n)
    for (int x : os) cout << x << " ";  // 1 5 7
    cout << "\n";

    // Insert element - O(log n)
    os.insert(4);

    // Check order after insert
    cout << *os.find_by_order(2) << "\n"; // 4

    return 0;
}
