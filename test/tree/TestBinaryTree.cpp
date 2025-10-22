#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "tree/BinaryTree.h"

TEST_CASE("Test Binary Tree", "[tree]")
{
   struct TestStruct
   {
      uint32_t a;
      uint64_t b;
   };

   BinaryTree::BinaryTree<TestStruct> Tree;
   Tree.EmplaceNode(3UL, 5ULL);
   Tree.EmplaceNode(6UL, 7ULL);
   REQUIRE(Tree.GetNodes().size() == 2);
}
