#include <ranges>
#include "graph/micemaze.h"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("MiceMaze", "[graph]")
{
   std::vector<Graphs::GraphEdgeData> EdgeData;
   // Make reverse graph so we can do a 1 pass
   // Swap To and From by hand
   EdgeData.emplace_back(1, 0, 12);
   EdgeData.emplace_back(2, 0, 6);
   EdgeData.emplace_back(3, 0, 45);
   EdgeData.emplace_back(4, 0, 7);
   EdgeData.emplace_back(0, 1, 26);
   EdgeData.emplace_back(3, 1, 9);
   EdgeData.emplace_back(1, 2, 2);
   EdgeData.emplace_back(2, 3, 8);
   EdgeData.emplace_back(1, 4, 21);

   // Range factory
   auto NodeData = std::views::iota(0u, 5u) | std::ranges::to<std::vector<int>>();
   // Just associate some index with each node.
   MiceMaze::GraphType Graph{std::move(NodeData), std::move(EdgeData)};

   const auto Result{MiceMaze::MiceMaze(5, 0, 50, Graph)};

   CHECK(Result.size() == 4);

   // Only arrows away from exit node so we can't actually reach it.
   EdgeData = {};
   EdgeData.emplace_back(0, 1, 6);
   EdgeData.emplace_back(1, 2, 3);
   EdgeData.emplace_back(2, 3, 7);

   auto                NodeData2 = std::views::iota(0u, 4u) | std::ranges::to<std::vector<int>>();
   MiceMaze::GraphType Graph2{std::move(NodeData2), std::move(EdgeData), Graphs::ReverseGraphTag};

   const auto Result2{MiceMaze::MiceMaze(4, 0, 30, Graph2)};
   CHECK(Result2.size() == 0);

   // Normal single file graph. Arrowsl eading back to start.
   EdgeData = {};
   EdgeData.emplace_back(1, 0, 6);
   EdgeData.emplace_back(2, 1, 3);
   EdgeData.emplace_back(3, 2, 7);

   auto                NodeData3 = std::views::iota(0u, 4u) | std::ranges::to<std::vector<int>>();
   MiceMaze::GraphType Graph3{std::move(NodeData2), std::move(EdgeData), Graphs::ReverseGraphTag};
   const auto          Result3{MiceMaze::MiceMaze(4, 0, 30, Graph3)};
   CHECK(Result3.size() == 3);
}
