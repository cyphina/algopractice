#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "core/HashUtils.h"

TEST_CASE("Test Hashmap", "[hash]")
{
   HashUtils::HashTable<int, std::string> TestMap;
   TestMap.Emplace(5, "wee");
   REQUIRE(TestMap.Find(5) != nullptr);
}
