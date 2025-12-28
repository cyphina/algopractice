#include <print>
#include <random>

namespace
{
   void TestGenerateRandomNumbers()
   {
      std::random_device Seeder;
      std::mt19937       Engine{Seeder()};
      // Notice that these values are inclusive
      std::uniform_int_distribution<int> Distribution{1, 99};
      std::println("{}", Distribution(Engine));
   }
}

int main()
{
   TestGenerateRandomNumbers();
}
