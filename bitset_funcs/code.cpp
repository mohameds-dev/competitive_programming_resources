// bit_utils.hpp
#pragma once
#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Convert string of bits ("1011") to long long
ll bitset_to_ll(const string &s) {
    return (ll)bitset<64>(s).to_ullong();
}

// Convert long long to bitset string of length n
string ll_to_bitset(ll x, int n = 64) {
    bitset<64> b(x);
    string s = b.to_string();
    return s.substr(64 - n, n);
}

// Count number of set bits
int count_bits(ll x) {
    return (int)bitset<64>(x).count();
}

// Check if k-th bit (0-indexed from right) is set
bool get_bit(ll x, int k) {
    return (x >> k) & 1LL;
}

// Set k-th bit
ll set_bit(ll x, int k) {
    return x | (1LL << k);
}

// Clear k-th bit
ll clear_bit(ll x, int k) {
    return x & ~(1LL << k);
}

// Toggle k-th bit
ll toggle_bit(ll x, int k) {
    return x ^ (1LL << k);
}

// Get lowest set bit position (1-indexed). Returns 0 if none.
int lowest_set_bit_pos(ll x) {
    if (x == 0) return 0;
    return __builtin_ctzll(x) + 1;
}

// Get highest set bit position (1-indexed). Returns 0 if none.
int highest_set_bit_pos(ll x) {
    if (x == 0) return 0;
    return 64 - __builtin_clzll(x);
}
