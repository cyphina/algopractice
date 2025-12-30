#include "RandomUtils.h"
#include <random>

namespace RandomUtils
{
   int GenerateUniformRandom(int InclusiveStart, int InclusiveEnd)
   {
      std::random_device Seeder;
      std::minstd_rand   Engine{Seeder()};

      std::uniform_int_distribution Distribution{InclusiveStart, InclusiveEnd};

      return Distribution(Engine);
   }
}
