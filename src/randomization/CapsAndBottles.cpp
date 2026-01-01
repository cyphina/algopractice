#include <ranges>

#include "CapsAndBottles.h"

#include "core/DebugUtils.h"
#include "core/RandomUtils.h"

namespace
{
   void MatchCapsAndBottlesImpl(const std::vector<uint32_t>& CapIndices, const std::vector<uint32_t>& BottleIndices,
                                const std::vector<uint32_t>& CapSizes, const std::vector<uint32_t>& BottleSizes,
                                CapsAndBottles::CapToBottleIndices& Results)
   {
      if(CapIndices.empty() || BottleIndices.empty())
      {
         return;
      }

      const auto RandomCapIndexInIndices{
          RandomUtils::GenerateUniformRandom(0, static_cast<int>(CapIndices.size() - 1))};
      const auto RandomCapIndex{CapIndices[RandomCapIndexInIndices]};

      // The book just makes them size n for safety
      std::vector<uint32_t> SmallerCapIndices;
      SmallerCapIndices.reserve(CapIndices.size());
      std::vector<uint32_t> LargerCapIndices;
      LargerCapIndices.reserve(CapIndices.size());
      std::vector<uint32_t> SmallerBottleIndices;
      SmallerBottleIndices.reserve(BottleIndices.size());
      std::vector<uint32_t> LargerBottleIndices;
      LargerBottleIndices.reserve(BottleIndices.size());

      const auto RandomCapSize{CapSizes[RandomCapIndex]};

      for(const auto BottleIndex : BottleIndices)
      {
         if(BottleSizes[BottleIndex] < RandomCapSize)
         {
            SmallerBottleIndices.push_back(BottleIndex);
         }
         else if(BottleSizes[BottleIndex] > RandomCapSize)
         {
            LargerBottleIndices.push_back(BottleIndex);
         }
         else
         {
            Results.emplace_back(RandomCapIndex, BottleIndex);
         }
      }

      for(const auto CapIndex : CapIndices)
      {
         if(CapSizes[CapIndex] < RandomCapSize)
         {
            SmallerCapIndices.emplace_back(CapIndex);
         }
         else if(CapSizes[CapIndex] > RandomCapSize)
         {
            LargerCapIndices.emplace_back(CapIndex);
         }
      }

      MatchCapsAndBottlesImpl(SmallerCapIndices, SmallerBottleIndices, CapSizes, BottleSizes, Results);
      MatchCapsAndBottlesImpl(LargerCapIndices, LargerBottleIndices, CapSizes, BottleSizes, Results);
   }
}

namespace CapsAndBottles
{
   CapToBottleIndices MatchCapsAndBottles(const std::vector<uint32_t>& CapSizes,
                                          const std::vector<uint32_t>& BottleSizes)
   {
      if(ensure(CapSizes.size() == BottleSizes.size()))
      {
         if(CapSizes.empty())
         {
            return {};
         }

         std::vector        CapIndices(std::from_range, std::views::iota(0u, CapSizes.size()));
         std::vector        BottleIndices{std::from_range, std::views::iota(0u, BottleSizes.size())};
         CapToBottleIndices Results;

         MatchCapsAndBottlesImpl(CapIndices, BottleIndices, CapSizes, BottleSizes, Results);

         return Results;
      }

      return {};
   }
}
