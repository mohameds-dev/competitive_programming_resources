#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod = 1e9 + 7;
ll fact[2009], inv[2009];

// Fast exponentiation: b^e mod m
ll fastPower(ll b, ll e, ll m) {
    if (e == 0) return 1;
    ll hp = fastPower(b, e / 2, m);
    hp = (hp * hp) % m;
    if (e % 2) hp = (hp * b) % m;
    return hp % m;
}

// Modular inverse using Fermat's little theorem
ll modularInverse(ll b, ll m) {
    return fastPower(b, m - 2, m);
}

// Precompute factorials and inverses up to mx
void factorials(int mx) {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < mx; i++) {
        fact[i] = (i * fact[i - 1]) % mod;
        inv[i] = modularInverse(fact[i], mod);
    }
}

// Compute nCr mod m
ll nCr(ll n, ll r, ll m) {
    if (r < 0 || r > n) return 0;
    ll a = fact[n];
    ll b = (inv[n - r] * inv[r]) % m;
    return (a * b) % m;
}