#include <ranges>
#include "core/Grid.h"
#include "graph/grandmaplanner.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("GrandmaPlanner", "[graph]")
{
   std::vector<int>          NodeData{std::views::iota(0, 4) | std::ranges::to<std::vector<int>>()};
   Core::Grid<int>           AdjacencyMatrix({{0, 3, 8, 2}, {3, 0, 2, 1}, {8, 2, 0, 5}, {2, 1, 5, 0}});
   GrandmaPlanner::GraphType Graph{std::move(NodeData), std::move(AdjacencyMatrix)};

   std::unordered_set<uint32_t> CookieHouseIndices({2});
   const auto                   Result{GrandmaPlanner::GrandmaPlanner(Graph, CookieHouseIndices)};

   // 0 -> 1 -> 2 -> 1 -> 3
   CHECK(Result->MinDist == 8);

   std::unordered_set<uint32_t> CookieHouseIndices2({1});
   const auto                   Result2{GrandmaPlanner::GrandmaPlanner(Graph, CookieHouseIndices2)};

   CHECK(Result2->MinDist == 4);
}
