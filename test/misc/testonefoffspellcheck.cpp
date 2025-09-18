#include <catch2/catch_test_macros.hpp>
#include "misc/oneoffspellcheck.h"

TEST_CASE("Test OneOffSpellCheck", "[spellcheck]")
{
   const auto Result{OneOffSpellCheck::IsStringOneOff("abc", "xabc")};
   REQUIRE((Result->first == 0 && Result->second == 1));
   const auto Result2{OneOffSpellCheck::IsStringOneOff("abcd", "abcdx")};
   REQUIRE((Result2->first == 4 && Result2->second == 5));
   const auto Result3{OneOffSpellCheck::IsStringOneOff("axxy", "axxxy")};
   REQUIRE((Result3->first == 1 && Result3->second == 4));
   const auto Result4{OneOffSpellCheck::IsStringOneOff("xxxxxxxxx", "xxxxxxxxxx")};
   REQUIRE((Result4->first == 0 && Result4->second == 10));
   const auto Result5{OneOffSpellCheck::IsStringOneOff("abcdxxexxf", "abcdxxexxxf")};
   REQUIRE((Result5->first == 7 && Result5->second == 10));
   const auto Result6{OneOffSpellCheck::IsStringOneOff("a", "ab")};
   REQUIRE((Result6->first == 1 && Result5->second == 2));
   REQUIRE(OneOffSpellCheck::IsStringOneOff("abasdfasdf", "abdsdfaddf").has_value() == false);
}
