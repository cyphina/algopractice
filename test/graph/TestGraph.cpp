#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "graph/graph.h"

TEST_CASE("Test Graph", "[graph]")
{
   std::unique_ptr<Graph::Node<int>> Node{std::make_unique<Graph::Node<int>>(5)};

   Graph::Graph<int> Graph;
}
