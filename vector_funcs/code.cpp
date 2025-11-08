#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

int main() {
    vector<int> base = {5, 1, 3, 9, 7, 3};

    // accumulate (sum) and partial_sum (prefix sums)
    {
        vector<int> v = base;
        accumulate(all(v), 0); // sum = 28
        vector<int> pref(v.size());
        partial_sum(all(v), pref.begin()); // pref = {5, 6, 9, 18, 25, 28}
    }

    // count, find, any_of / all_of / none_of (O(n) time)
    {
        vector<int> v = base;
        count(all(v), 3);            // 2
        any_of(all(v), [](int x){return x > 8;}); // true
        all_of(all(v), [](int x){return x < 10;}); // true
        none_of(all(v), [](int x){return x < 0;}); // true
    }

    // lower_bound / upper_bound (O(log n) on sorted vector)
    {
        vector<int> v = base;
        sort(all(v));                // v = {1, 3, 3, 5, 7, 9}
        int x = 3;
        auto lb = lower_bound(all(v), x); // index = 1
        auto ub = upper_bound(all(v), x); // index = 3
    }

    // "Inverse" (descending) logic
    // lower_bound / upper_bound (O(log n) on sorted vector)
    {
        vector<int> v = base;
        sort(all(v), greater<int>());   // v = {9, 7, 5, 3, 3, 1}
        int x = 3;

        // MUST pass greater<int>() to lower_bound
        auto lb = lower_bound(all(v), x, greater<int>());
        // Logic: first 'x' such that !(x > 3), i.e., x <= 3
        // To get index: distance(v.begin(), lb) -> 3 (points to the first 3)

        // MUST pass greater<int>() to upper_bound
        auto ub = upper_bound(all(v), x, greater<int>());
        // Logic: first 'x' such that (3 > x), i.e., x < 3
        // To get index: distance(v.begin(), ub) -> 5 (points to the 1)
    }

    // unique + erase (deduplicate sorted vector, O(n) time)
    {
        vector<int> v = base;
        sort(all(v));                // v = {1, 3, 3, 5, 7, 9}
        v.erase(unique(all(v)), v.end()); // v = {1, 3, 5, 7, 9}
    }

    // next_permutation / prev_permutation (O(n) time)
    {
        vector<int> v = {1, 2, 3};
        next_permutation(all(v));    // v = {1, 3, 2}
        prev_permutation(all(v));    // v = {1, 2, 3}
    }

    // nth_element (k-th order statistic, avg O(n))
    {
        vector<int> v = base;
        int k = 2;
        nth_element(v.begin(), v.begin() + k, v.end());
        v[k]; // 3 (3rd smallest element)
    }

    // sort with custom comparator (O(n log n))
    {
        vector<int> v = base;
        sort(all(v), [](int a, int b){
            if(a % 10 == b % 10) return a < b;
            return (a % 10) < (b % 10);
        }); 
        // v = {1, 3, 3, 5, 7, 9} (sorted by last digit, ties by value)
    }

    // set operations on sorted vectors (O(n + m) time)
    {
        vector<int> a = {1, 2, 3, 4, 5};
        vector<int> b = {3, 4, 5, 6, 7};
        vector<int> res;

        set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));          
        // res = {1, 2, 3, 4, 5, 6, 7}

        res.clear();
        set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));   
        // res = {3, 4, 5}

        res.clear();
        set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
        // res = {1, 2}
    }

    return 0;
}
