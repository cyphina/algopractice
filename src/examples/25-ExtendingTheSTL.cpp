#include <memory>
#include <print>
#include <set>
#include <vector>
#include "graph/digraph.h"

struct Something
{
   int Wee{};
};

void TestAllocator()
{
   std::allocator<Something> Alloc;
   // Allocate unitialized memory block for 1 instance of Something
   auto* Memory{Alloc.allocate(2)};
   // Placement new to construct a Something in the block.
   ::new(Memory) Something{3};
   ::new(Memory + 1) Something{5};

   std::println("{} {}", Memory->Wee, (Memory + 1)->Wee);

   // Destroy class instance (call destructor)
   std::destroy_n(Memory, 2);
   Alloc.deallocate(Memory, 2);
   Memory = nullptr;
}

// Indirect unary predicate means it takes in the type that the iterator points to not the type of the iterator.
// It adds iterator to the found element to destination list.
// Sentinel for means first != last is valid.
template <std::forward_iterator ForwardIterator, std::sentinel_for<ForwardIterator> Sentinel,
          std::output_iterator<ForwardIterator>          OutputIterator, typename Projection = std::identity,
          std::indirect_unary_predicate<ForwardIterator> Predicate>
OutputIterator find_all(ForwardIterator first, Sentinel last, OutputIterator dest, Predicate pred, Projection proj)
{
   while(first != last)
   {
      if(std::invoke(pred, std::invoke(proj, *first)))
      {
         *dest = first;
         ++dest;
      }
      ++first;
   }
   return dest;
}

void TestFindAll()
{
   std::vector<int> Test{
       1, 2, 3, 4, 5,
   };
   std::vector<std::vector<int>::iterator> Matches;
   find_all(
       Test.begin(), Test.end(), std::back_insert_iterator(Matches),
       [](const int& Item)
       {
          return Item % 2 == 0;
       },
       [](const int& Item)
       {
          return Item + 1;
       });

   for(const auto& Match : Matches)
   {
      std::println("Found Match at: {}", std::distance(Test.begin(), Match));
   }
}

void TestDirectedGraph()
{
   digraph::directed_graph<int> Graph;
}

int main()
{
   TestAllocator();
   TestFindAll();
}
