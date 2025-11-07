#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(),x.end()

// print vector neatly
template <typename T>
void print_vec(const vector<T>& v, string name = "") {
    if (!name.empty()) cout << name << " = ";
    cout << "[ ";
    for (auto& x : v) cout << x << " ";
    cout << "]\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> base = {5, 1, 3, 9, 7, 3};

    print_vec(base, "base");

    // accumulate (sum) and partial_sum (prefix sums)
    {
        vector<int> v = base;
        cout << "sum = " << accumulate(all(v), 0) << "\n";         
        vector<int> pref(v.size());
        partial_sum(all(v), pref.begin());        
        print_vec(pref, "partial (prefix) sum");
    }

    // count, find, any_of / all_of / none_of (each is O(n) time, O(1) space)
    {
        vector<int> v = base;
        cout << "count(3) = " << count(all(v), 3) << "\n";          
        cout << boolalpha; // makes booleans printed as 'true' and 'false'
        cout << "any_of(>8): " << any_of(all(v), [](int x){return x > 8;}) << "\n";  
        cout << "all_of(<10): " << all_of(all(v), [](int x){return x < 10;}) << "\n"; 
        cout << "none_of(<0): " << none_of(all(v), [](int x){return x < 0;}) << "\n";
        cout << noboolalpha; // disables boolalpha
    }

    // lower_bound / upper_bound (binary search helpers)
    {
        vector<int> v = base;
        sort(all(v));                                                
        int x = 3;
        auto lb = lower_bound(all(v), x);                            
        auto ub = upper_bound(all(v), x);                            
        cout << "lower_bound(3) index = " << (lb - v.begin())
             << ", upper_bound(3) index = " << (ub - v.begin()) << "\n";
    }

    // unique + erase (deduplicate sorted vector)
    {
        vector<int> v = base;
        sort(all(v));                                                
        // O(n log n) time, O(1) space
        v.erase(unique(all(v)), v.end());                            
        // O(n) time, O(1) space
        print_vec(v, "unique");
    }

    // next_permutation / prev_permutation
    {
        vector<int> v = {1, 2, 3};
        next_permutation(all(v));                                    
        // O(n) time, O(1) space
        print_vec(v, "next_permutation");
        prev_permutation(all(v));                                    
        // O(n) time, O(1) space
        print_vec(v, "prev_permutation");
    }

    // nth_element (find k-th order statistic without sorting)
    //  more than ONE query, sort instead
    {
        vector<int> v = base;
        int k = 2;
        nth_element(v.begin(), v.begin() + k, v.end());              
        // O(n) avg, O(n^2) worst (extremely rare), O(1) space
        cout << "3rd smallest = " << v[k] << "\n";
    }

    // sort with custom comparator (e.g., by last digit)
    {
        vector<int> v = base;
        sort(all(v), [](int a, int b) {
            if (a % 10 == b % 10) return a < b;
            return (a % 10) < (b % 10);
        });                                                          
        // O(n log n) time, O(1) space
        print_vec(v, "custom sort (by last digit)");
    }

    // set operations on sorted vectors
    {
        vector<int> a = {1, 2, 3, 4, 5};
        vector<int> b = {3, 4, 5, 6, 7};
        vector<int> res;

        set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));          
        // O(n + m) time, O(n + m) space
        print_vec(res, "set_union");

        res.clear();
        set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));   
        // O(n + m) time, O(min(n, m)) space
        print_vec(res, "set_intersection");

        res.clear();
        set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
        // O(n + m) time, O(n) space
        print_vec(res, "set_difference");
    }

    return 0;
}
