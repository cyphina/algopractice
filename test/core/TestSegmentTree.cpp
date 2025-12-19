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
