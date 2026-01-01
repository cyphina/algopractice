#include <iterator>
#include <print>
#include <ranges>
#include <vector>
namespace
{
   void TestIterator()
   {
      std::vector<int> V{3, 1, 4};
      std::println("Iterator Distance - {} {}", std::distance(V.begin() + 1, V.end()),
                   std::distance(V.end() - 1, V.begin()));
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
}

int main()
{
   TestIterator();
   TestRangeAdapter();
   TestSubrange();
}
