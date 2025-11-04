#include <catch2/catch_test_macros.hpp>
#include "graph/graph.h"

TEST_CASE("Test Graph", "[graph]")
{
   Graphs::Graph<int> Graph;

   auto* A{Graph.InsertNode(Graphs::Node{5})};
   auto* B{Graph.EmplaceNode(5)};

   Graph.AddUndirectedEdge(A, B);

   REQUIRE(Graph.GetNodes().size() == 2);
   REQUIRE(A->Edges.size() == 1);
   REQUIRE(B->Edges.size() == 1);
}
