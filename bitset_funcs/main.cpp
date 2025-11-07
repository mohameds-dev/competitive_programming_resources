#include <bits/stdc++.h>
using namespace std;
#define ll long long

#include <bitset>

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

int main() {
    string s = "1011";
    ll x = bitset_to_ll(s);
    cout << "bitset_to_ll: " << x << "\n";
    cout << "ll_to_bitset: " << ll_to_bitset(x, 4) << "\n";
    cout << "count_bits: " << count_bits(x) << "\n";
    cout << "get_bit(1): " << get_bit(x, 1) << "\n";
    cout << "set_bit(4): " << ll_to_bitset(set_bit(x, 4), 5) << "\n";
    cout << "clear_bit(1): " << ll_to_bitset(clear_bit(x, 1), 4) << "\n";
    cout << "toggle_bit(0): " << ll_to_bitset(toggle_bit(x, 0), 4) << "\n";
    cout << "lowest_set_bit_pos: " << lowest_set_bit_pos(x) << "\n";
    cout << "highest_set_bit_pos: " << highest_set_bit_pos(x) << "\n";
}
