#include "graph/micemaze.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("MiceMaze", "[graph]")
{
   std::vector<Graphs::GraphEdgeData> EdgeData;
   // Make reverse graph so we can do a 1 pass
   // Swap To and From
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
   const auto NodeData = std::views::iota(0u, 5u) | std::ranges::to<std::vector<int>>();
   // Just associate some index with each node.
   MiceMaze::GraphType Graph{std::move(NodeData), std::move(EdgeData)};

   const auto Result{MiceMaze::MiceMaze(5, 0, 50, Graph)};

   CHECK(Result.size() == 5);
}
