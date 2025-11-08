/*
USAGE:
    - Adjust M (mod) or base primes (P1, P2) as needed.
    - Call pre() once before all tests to precompute powers and inverses.
    - Construct Hash(s) for a string.
    - Use getRangeHashVal(l, r) for inclusive substring hash.
    Hashing supports double mod-bases (P1, P2) to reduce collisions.
*/

#include <bits/stdc++.h>
using namespace std;

// Constants
const int N = 3 * 1e5 + 5, P1 = 31, P2 = 37, M = 1e9 + 7;
int pw1[N], pw2[N], inv1[N], inv2[N];

// Modular multiplication and addition
void apply_mod(int &a)
{
    a = ((a % M) + M) % M;
}
int mul(int a, int b)
{
    apply_mod(a);
    apply_mod(b);
    return (1LL * a * b) % M;
}
int add(int a, int b)
{
    apply_mod(a);
    apply_mod(b);
    return (a + b) % M;
}

// Rolling hash with prefix storage
struct Hash
{
    vector<pair<int, int>> prefixHash;

    // O(n): Precompute prefix hash values
    Hash(string s)
    {
        prefixHash = vector<pair<int, int>>(s.size(), {0, 0});
        for (int i = 0; i < (int)s.size(); i++)
        {
            prefixHash[i].first = mul(s[i] - 'a' + 1, pw1[i]);
            prefixHash[i].second = mul(s[i] - 'a' + 1, pw2[i]);
            if (i)
                prefixHash[i] = {
                    add(prefixHash[i].first, prefixHash[i - 1].first),
                    add(prefixHash[i].second, prefixHash[i - 1].second)};
        }
    }

    // Return full string hash
    pair<int, int> getHashVal()
    {
        return prefixHash.back();
    }

    // O(1): Substring hash for inclusive range [l, r]
    pair<int, int> getRangeHashVal(int l, int r)
    {
        return {
            mul(add(prefixHash[r].first, -(l ? prefixHash[l - 1].first : 0)), inv1[l]),
            mul(add(prefixHash[r].second, -(l ? prefixHash[l - 1].second : 0)), inv2[l])};
    }
};

// Fast modular exponentiation - O(log power)
int fastPower(int base, int power)
{
    if (!power)
        return 1;
    int ret = fastPower(base, power >> 1);
    ret = mul(ret, ret);
    if (power & 1)
        ret = mul(ret, base);
    return ret;
}

// O(N): Precompute powers and modular inverses
void preprocess()
{
    pw1[0] = inv1[0] = pw2[0] = inv2[0] = 1;
    int mulInv1 = fastPower(P1, M - 2);
    int mulInv2 = fastPower(P2, M - 2);
    for (int i = 1; i < N; i++)
    {
        pw1[i] = mul(pw1[i - 1], P1);
        pw2[i] = mul(pw2[i - 1], P2);
        inv1[i] = mul(inv1[i - 1], mulInv1);
        inv2[i] = mul(inv2[i - 1], mulInv2);
    }
}
