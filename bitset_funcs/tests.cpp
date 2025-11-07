#define CATCH_CONFIG_MAIN
#include "../utils/catch2.hpp"
#include "code.cpp"

TEST_CASE("Bit utilities basic tests", "[bit_utils]") {
    ll x = bitset_to_ll("1011"); // 11

    SECTION("bitset_to_ll / ll_to_bitset") {
        REQUIRE(x == 11);
        REQUIRE(ll_to_bitset(x, 4) == "1011");
        REQUIRE(ll_to_bitset(x, 8) == "00001011");
    }

    SECTION("count_bits / get_bit") {
        REQUIRE(count_bits(x) == 3);
        REQUIRE(get_bit(x, 0) == true);
        REQUIRE(get_bit(x, 1) == true);
        REQUIRE(get_bit(x, 2) == false);
        REQUIRE(get_bit(x, 3) == true);
    }

    SECTION("set_bit / clear_bit / toggle_bit") {
        REQUIRE(ll_to_bitset(set_bit(x, 4), 5) == "11011");
        REQUIRE(ll_to_bitset(clear_bit(x, 1), 4) == "1001");
        REQUIRE(ll_to_bitset(toggle_bit(x, 0), 4) == "1010");
    }

    SECTION("lowest_set_bit_pos / highest_set_bit_pos") {
        REQUIRE(lowest_set_bit_pos(x) == 1);  // 1-indexed
        REQUIRE(highest_set_bit_pos(x) == 4); // 1-indexed
        REQUIRE(lowest_set_bit_pos(0) == 0);
        REQUIRE(highest_set_bit_pos(0) == 0);
    }
}
