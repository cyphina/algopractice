#include <print>

namespace
{
   struct Vector
   {
      float X{};
      float Y{};
      float Z{};
   };

   void TestStructuredBindings()
   {
      Vector Test{1, 2, 3};
      const auto& [X, Y, Z]{Test};
      std::println("{} {} {}", X, Y, Z);
      auto& [X2, Y2, Z2]{Test};
      X2 = 5;
      // Prints 5
      std::println("{}", Test.X);
      auto [X3, Y3, Z3]{Test};
      X3 = 7;
      // Prints 5
      std::println("{}", Test.X);
   }
}

int main()
{
   TestStructuredBindings();
}
