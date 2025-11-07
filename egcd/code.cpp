#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Extended Euclidean Algorithm
// Returns gcd(a, b) and finds x, y such that a*x + b*y = gcd(a, b)
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {         // Base case
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, x1, y1);  // Recurse
    x = y1;                    // Update x
    y = x1 - (a / b) * y1;     // Update y
    return g;                  // Return gcd
}
// Time complexity: O(log(max(a, b)))
