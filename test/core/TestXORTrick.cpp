#include <string>
#include "core/StringUtils.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("String Utils", "[string]")
{
   constexpr const char* First{"Your Mom"};
   constexpr const char* Second{"Go Bird!"};

   std::string A{First};
   std::string B{Second};

   // Remember this doens't break aliasing since std::byte is a type meant for raw memory operations and is allowed to alias this data.
   // Bit-cast is used in t he opposite direction (from std::byte to something else).
   StringUtils::Xor_Swap_Bytes(std::span(reinterpret_cast<std::byte*>(A.data()), A.size()),
                               std::span(reinterpret_cast<std::byte*>(B.data()), B.size()));

   REQUIRE(A == Second);
   REQUIRE(B == First);
}
