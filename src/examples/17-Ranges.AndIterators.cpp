#include <algorithm>
#include <deque>
#include <iterator>
#include <print>
#include <ranges>
#include <unordered_set>
#include <vector>
#include "core/DebugUtils.h"

namespace
{
   void TestIterator()
   {
      std::vector<int> V{3, 1, 4};
      std::println("Iterator Distance - {} {}", std::distance(V.begin() + 1, V.end()),
                   std::distance(V.end() - 1, V.begin()));
   }

   void TestReverseIterator()
   {
      std::vector<int> V{1, 2, 3, 4, 5};
      // Reverse printing
      std::println("Reverse Printing");
      for(size_t i = V.size(); i-- > 0;)
      {
         std::print("{} ", V[i]);
      }
      std::print("\n");
      std::for_each(V.rbegin(), V.rend(), // NOLINT(modernize-use-ranges)
                    [](int Elem)
                    {
                       std::print("{} ", Elem);
                    });
      std::print("\n");
      std::ranges::for_each(std::ranges::reverse_view(V),
                            [](int Elem)
                            {
                               std::print("{} ", Elem);
                            });
      std::print("\n");
   }
}

void TestIteratorAdapter()
{
   // Don't need to size destination
   std::vector<int> VectorA{1, 2, 3, 4, 5};
   std::vector<int> Dest;
   std::deque<int>  Dest2;

   // Take a reference to the container we're going to refer to an call push_back
   std::back_insert_iterator Inserter{Dest};
   // Or we can use the helper function instead the constructor (useful before CTAD).
   std::ranges::copy(VectorA, Inserter);
   std::println("Push Back{}", Dest);

   // Uses push_front (needs a deque since vector doesn't support this)
   std::ranges::copy(VectorA, std::front_inserter(Dest2));
   std::println("Push Front {}", Dest2);

   // Uses insert to start pushing after first element onwards.
   std::ranges::copy(VectorA, std::insert_iterator(Dest2, std::next(Dest2.begin())));
   std::println("After Insert {}", Dest2);

   std::vector             VectorB{1, 2, 3, 4, 5};
   std::unordered_set<int> SetOne;
   std::ranges::copy(VectorB, std::insert_iterator(SetOne, std::begin(SetOne)));
   std::println("Insert to Set {}", SetOne);
}

void TestMoveIteratorAdapter()
{
   std::vector<Test::TestCopyVsAssign> VectorA(5);
   std::println("Copy Constructor Move Iterator");
   std::vector<Test::TestCopyVsAssign> VectorB(std::move_iterator(VectorA.begin()), std::move_iterator(VectorA.end()));
   std::vector<Test::TestCopyVsAssign> VectorC(5);
   std::println("Copy Algorithm Move Iterator");
   std::copy(std::move_iterator(VectorA.begin()), std::move_iterator(VectorA.end()), VectorC.begin());
   std::vector<Test::TestCopyVsAssign> VectorD(5);
   std::println("Move Algorithm");
   std::ranges::move(VectorA, VectorD.begin());
}

void TestRangeAdapter()
{
   std::vector<int> Vec{1, 2, 3, 4, 5};
   const auto       Pred{[](int Elem) static
                   {
                      return Elem % 2 == 0;
                   }};

   // Some views you can't iterate when const like this.
   auto ReverseResult{Vec | std::views::filter(Pred) | std::views::reverse};

   std::println("Range Adapter Filter {}", ReverseResult);
}

void TestSubrange()
{
   std::vector<int> V{1, 2, 3, 4, 5};
   auto             It1{std::ranges::find(V, 2)};
   auto             It2{std::ranges::find(V, 4)};
   auto             Rng{std::ranges::subrange(It1, It2)};
   std::println("Subrange - {}", Rng);
}

int main()
{
   TestIterator();
   TestReverseIterator();
   TestIteratorAdapter();
   TestMoveIteratorAdapter();
   TestRangeAdapter();
   TestSubrange();
}
