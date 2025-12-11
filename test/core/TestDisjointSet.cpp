#include <cstdint>
#include "core/DisjointSet.h"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Disjoint Set", "[ds]")
{
   DisjointSet::DisjointSet<uint32_t> Data;
   Data.Add(1);
   Data.Add(2);
   Data.Add(3);
   Data.Add(4);
   Data.Add(5);
   Data.Add(6);
   Data.Add(7);

   Data.Unite(1, 2);
   Data.Unite(2, 3);
   Data.Unite(3, 4);
   Data.Unite(4, 5);
   Data.Unite(5, 6);
   Data.Unite(6, 7);

   CHECK(Data.Same(1, 2));
   CHECK(Data.Size(6) == 0);
   CHECK(Data.Size(1) == 7);
}
