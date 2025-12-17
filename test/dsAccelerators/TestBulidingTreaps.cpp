#include <print>
#include <vector>
#include "dsAccelerators/buildingtreaps.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Building Treaps Slow", "[treaps]")
{
   std::vector<BuildingTreaps::TreapNode> Nodes{{"A", 54}, {"I", 16}, {"K", 39}, {"E", 36}, {"B", 42}, {"G", 55},
                                                {"D", 49}, {"H", 56}, {"C", 58}, {"J", 40}, {"F", 5}};

   const auto TreapString{BuildingTreaps::GenerateTreapString(Nodes)};
   CHECK(TreapString == "((A/54(B/42))C/58(((D/49(E/36(F/5)))G/55)H/56((I/16)J/40(K/39))))");
}
