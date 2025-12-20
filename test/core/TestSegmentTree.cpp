#include <print>

#include "core/SegmentTree.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Segment Tree Creation", "[segmenttree]")
{
   std::vector<int>                 Data{54, 42, 58, 49, 36, 5, 55, 56, 16, 40, 39};
   SegmentTree::Mergeable<int> auto X{SegmentTree::MaxMerge<int>()};

   SegmentTree::SegmentTree SegTree{Data};

   SegTree.Print();
}

TEST_CASE("Segment Tree Query", "[segmenttree]")
{
   std::vector<int>                 Data{54, 42, 58, 49, 36, 5, 55, 56, 16, 40, 39};
   SegmentTree::Mergeable<int> auto X{SegmentTree::MaxMerge<int>()};

   SegmentTree::SegmentTree SegTree{Data};

   SECTION("Valid Queries")
   {
      const auto Query{SegTree.Query(2, 5)};
      CHECK(Query.value() == 58);

      const auto Query2{SegTree.Query(6, 10)};
      CHECK(Query2.value() == 56);
   }

   SECTION("Single Queries")
   {
      for(std::size_t i{0}; i < Data.size(); ++i)
      {
         const auto TestQuery{SegTree.Query(i, i + 1)};
         CHECK(TestQuery.value() == Data[i]);
      }
   }

   SECTION("Invalid Queries")
   {
      const auto Query{SegTree.Query(5, 2)};
      CHECK(!Query.has_value());
   }

   SECTION("Entire Range Query")
   {
      const auto Query{SegTree.Query(0, Data.size())};
      CHECK(Query.value() == 58);
   }
}
