#include <catch2/catch_all.hpp>
#include "collection/array.hpp"

using namespace pulsar;

TEST_CASE("Check size.", "[Array]") {

	Array<uint32_t> items;
    REQUIRE(items.Size() == 0);
    REQUIRE(items.IsEmpty());
        
    items.Add(5);
    items.Add(4);
    items.Add(3);
    items.Add(2);
    items.Add(1);
    items.Add(0);

	REQUIRE(items[0] == 5);
    REQUIRE(items[1] == 4);
}
