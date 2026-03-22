#include <bits/stdc++.h>
using namespace std;
#include "code.cpp"
#define ll long long

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
