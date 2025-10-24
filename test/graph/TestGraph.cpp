#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "graph/graph.h"

TEST_CASE("Test Graph", "[graph]")
{
   Graph::Graph<int> Graph;

   Graph.InsertNode(Graph::Node{5});
   Graph.EmplaceNode(5);

   REQUIRE(Graph.GetNodes().size() == 2);
}
