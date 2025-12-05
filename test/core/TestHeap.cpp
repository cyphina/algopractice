#include <cstdint>
#include "core/DebugUtils.h"
#include "core/Heap.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Test STL Heap Creation", "[heap]")
{
   std::vector<uint32_t> Data{Test::RandomFillIntVec<uint32_t>(30)};
   //Heap::HeapComparator auto   Test{std::greater<>{}};
   Heap::HeapWithSTL<uint32_t> Heap{std::move(Data)};
   Heap.PrintData();
   REQUIRE(std::ranges::is_heap(Heap.GetData(), std::greater<>{}));
}

TEST_CASE("Test Heap Creation", "[heap]")
{
   std::vector<uint32_t> Data{Test::RandomFillIntVec<uint32_t>(30)};
   //Heap::HeapComparator auto   Test{std::greater<>{}};
   Heap::Heap<uint32_t> Heap{std::move(Data)};
   Heap.PrintData();
   REQUIRE(std::ranges::is_heap(Heap.GetData(), std::greater<>{}));
}

TEST_CASE("Test Heap Extraction", "[heap]")
{
   std::vector<uint32_t> Data{Test::RandomFillIntVec<uint32_t>(30)};
   //Heap::HeapComparator auto   Test{std::greater<>{}};
   Heap::Heap<uint32_t> Heap{std::move(Data)};
   const size_t         InitialHeapSize{Heap.Size()};
   for(size_t i{0}; i < InitialHeapSize; ++i)
   {
      const auto Min{Heap.ExtractTop()};
      REQUIRE(Min == i);
      REQUIRE(Heap.Size() == InitialHeapSize - (i + 1));
   }
}
