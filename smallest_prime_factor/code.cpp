#include <bits/stdc++.h>
using namespace std;

const int N = 1e7;        // Maximum number for preprocessing

int spf[N] = {};           // Smallest prime factor array

// Preprocess smallest prime factors for all numbers up to N
void preprocess() {
    spf[0] = spf[1] = 0;         // 0 and 1 are not prime
    for (int i = 2; i < N; ++i) spf[i] = i;  // Initialize spf[i] = i
    
    for (int i = 2; i * i < N; ++i) {
        if (spf[i] == i) {           // i is prime
            for (int j = i * i; j < N; j += i)
                if (spf[j] > i) spf[j] = i;  // Update smallest prime factor
        }
    }
}

// Time complexity: O(N log log N) using sieve
// Space complexity: O(N)

/* USAGE:

int x = 60;
vector<int> factors;
while (x > 1) {
    factors.push_back(spf[x]); // get smallest prime factor
    x /= spf[x];               // reduce x
}
*/
