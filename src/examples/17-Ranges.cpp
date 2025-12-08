#include <print>
#include <ranges>
#include <vector>

namespace
{
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
   TestSubrange();
}
