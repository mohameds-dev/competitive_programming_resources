#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
bool prime[N];

// Sieve of Eratosthenes: marks prime[i] = true if i is prime
// Time: O(N log log N), Space: O(N)
void sieve(int X) {
    memset(prime, true, sizeof prime);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= X; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= X; j += i) prime[j] = false;
        }
    }
}

