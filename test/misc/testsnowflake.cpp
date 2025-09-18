#include <array>
#include <catch2/catch_test_macros.hpp>
#include "misc/snowflake.h"

TEST_CASE("Test Snowflake", "[snowflake]")
{
   REQUIRE(Snowflake::isIdentical(std::array{1, 2, 3, 4, 5}, std::array{2, 3, 4, 5, 1}));
   REQUIRE(Snowflake::isIdentical(std::array{1, 2, 3, 4, 5}, std::array{2, 6, 4, 5, 1}) == false);
   REQUIRE(Snowflake::isIdentical(std::array{1, 2, 3, 4, 5}, std::array{3, 4, 5, 1, 2}));
}
