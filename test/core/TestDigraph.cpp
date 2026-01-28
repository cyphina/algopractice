
#include <print>
#include "Graph/digraph.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Digraph Functionality", "[digraph]")
{
   digraph::directed_graph<int> graph;
   // Insert some nodes and edges.
   graph.insert(11);
   graph.insert(22);
   graph.insert(33);
   graph.insert(44);
   graph.insert(55);
   graph.insert_edge(11, 33);
   graph.insert_edge(22, 33);
   graph.insert_edge(22, 44);
   graph.insert_edge(22, 55);

   graph.insert_edge(33, 44);
   graph.insert_edge(44, 55);

   SECTION("Printing")
   {
      std::println("{}", to_dot(graph, "Graph1"));
   }

   SECTION("Test Iterators")
   {
      for(auto& Node : graph)
      {
         std::println("{}", Node);
      }

      auto Result{std::find(graph.begin(), graph.end(), 22)};
      CHECK(Result != graph.end());
      CHECK(*Result == 22);
   }
}
