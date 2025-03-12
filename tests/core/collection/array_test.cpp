#include <catch2/catch_all.hpp>
#include "collection/array.hpp"

using namespace pulsar;

TEST_CASE("Adding elements to an array.", "[Array::Add]") {

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

TEST_CASE("Adding elements to an array corresponds correctly to the current size.", "[Array::Size]") {

	Array<uint32_t> items;
    REQUIRE(items.Size() == 0);
    REQUIRE(items.IsEmpty());
        
    items.Add(5);
    items.Add(4);
    items.Add(3);
    items.Add(2);
    items.Add(1);
    items.Add(0);

    REQUIRE(items.Size() == 6);
    REQUIRE_FALSE(items.IsEmpty());

    items.Pop();
    items.Pop();
    items.Pop();

    REQUIRE(items.Size() == 3);
}



