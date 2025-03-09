#include <catch2/catch_all.hpp>
#include "collection/hash_map.hpp"

using namespace pulsar;

TEST_CASE("Check insertion.", "[HashMap::Insert]") {

	HashMap<uint32_t, uint32_t> map;

    map.Insert(5, 8);
    REQUIRE(map.Get(5) == 8);
    map.Insert(5, 4);
    REQUIRE(map.Get(5) == 4);

    REQUIRE_FALSE(map.GetPtr(7));
    REQUIRE(*map.GetPtr(5) == 4);
    
    map.Insert(4141, 26);
    map.Insert(874, 11);
    map.Insert(95, 20);
    map.Insert(66, 82);
    map.Insert(10, 99);

    REQUIRE(map.Get(10) == 99);
    REQUIRE(map.Size() == 6);

    map[10] = 4;
    REQUIRE(map[10] == 4);
    REQUIRE(map.Size() == 6);

    map[12] = 12;
    REQUIRE(map[12] == 12);
    REQUIRE(map.Size() == 7);
}

TEST_CASE("Check if the hashmap contains an element.", "[HashMap::Contains]") {
    HashMap<uint32_t, uint32_t> map;

    map.Insert(5, 8);
    map.Insert(3, 4);

    REQUIRE(map.Contains(5));
    REQUIRE(map.Contains(3));

    REQUIRE(map.Size() == 2);
}

TEST_CASE("Check if the hashmap can remove an element.", "[HashMap::Remove]") {
    HashMap<uint32_t, uint32_t> map;

    map.Insert(5, 8);
    map.Insert(3, 4);

    REQUIRE(map.Contains(5));
    REQUIRE(map.Size() == 2);

    map.Remove(5);

    REQUIRE_FALSE(map.Contains(5));
    REQUIRE(map.Size() == 1);
}
