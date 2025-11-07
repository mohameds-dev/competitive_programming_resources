#define CATCH_CONFIG_MAIN
#include "code.cpp"
#include "../utils/catch2.hpp"

TEST_CASE("SPF sieve basic tests", "[spf]") {
    preprocess();
    
    // Factorize 60: 2 * 2 * 3 * 5
    int x = 60;
    vector<int> factors;
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    REQUIRE(factors == vector<int>{2,2,3,5});
    
    // Check primes
    REQUIRE(spf[2] == 2);
    REQUIRE(spf[13] == 13);
    
    // Non-prime
    REQUIRE(spf[12] == 2); // smallest prime factor of 12
}
