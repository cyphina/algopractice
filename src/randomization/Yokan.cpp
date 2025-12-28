#include "Yokan.h"
#include <algorithm>
#include <random>

namespace
{
   uint32_t CountNumFlavoredPiecesInSlab(const Yokan::FlavorIndices& FlavorIndices, uint32_t TargetFlavor,
                                         std::size_t LeftSlabInclusiveIndex, std::size_t RightSlabInclusiveIndex)
   {
      if(RightSlabInclusiveIndex < LeftSlabInclusiveIndex || TargetFlavor >= FlavorIndices.Data.size())
      {
         return 0;
      }

      const auto& TargetedFlavorIndices{FlavorIndices.Data[TargetFlavor]};

      if(TargetedFlavorIndices.empty())
      {
         return 0;
      }

      std::size_t Low{};
      std::size_t High{TargetedFlavorIndices.size()};

      // Example 2 - [3,6,9,10]
      // Parition by the LeftSlabInclusiveIndex

      // We have to use a binary search to a boundary position instead of our typical binary search find something.
      // Everything to the left of Low is < LeftSlabInclusiveIndex.

      while(Low < High)
      {
         std::size_t Mid{(Low + High) / 2};
         if(TargetedFlavorIndices[Mid] < LeftSlabInclusiveIndex)
         {
            Low = Mid + 1;
         }
         else
         {
            High = Mid;
         }
      }

      const auto ElementsLargerThanLeftStartIndex{Low};

      // Everything to the left of Right is < RightSlabInclusiveIndex so offset it.

      Low  = 0;
      High = TargetedFlavorIndices.size();

      while(Low < High)
      {
         std::size_t Mid{(Low + High) / 2};
         if(TargetedFlavorIndices[Mid] < RightSlabInclusiveIndex + 1)
         {
            Low = Mid + 1;
         }
         else
         {
            High = Mid;
         }
      }

      const auto ElementsEqualToAndSmallerThanRightEndIndex{Low};
      return ElementsEqualToAndSmallerThanRightEndIndex - ElementsLargerThanLeftStartIndex;
   }
}

namespace Yokan
{
   FlavorIndices::FlavorIndices(std::size_t InitialSize) : Data(InitialSize)
   {
   }

   FlavorIndices BuildFlavorIndices(uint32_t MaxPieceFlavor, const std::vector<uint32_t>& PieceFlavors)
   {
      FlavorIndices FlavorIndexLookup{MaxPieceFlavor};

      for(std::size_t PieceIndex{}; const auto& PieceFlavor : PieceFlavors)
      {
         FlavorIndexLookup.Data[PieceFlavor - 1].push_back(PieceIndex);
         ++PieceIndex;
      }

      return FlavorIndexLookup;
   }

   std::optional<YokanResult> YokanQuery(std::vector<uint32_t>& PieceFlavors, const FlavorIndices& FlavorIndexLookup,
                                         std::size_t LeftSlabInclusiveIndex, std::size_t RightSlabExclusiveIndex)

   {
      RightSlabExclusiveIndex = RightSlabExclusiveIndex - 1;
      if(LeftSlabInclusiveIndex > RightSlabExclusiveIndex || RightSlabExclusiveIndex > PieceFlavors.size())
      {
         return {};
      }

      static constexpr int NUM_GUESSES{30};
      // We have to take the slice and make guesses about what flavor to check. Given that a succesful flavor has to fill up at least 1/3 elements we can keep guessing random indices hoping that we hit an index that
      // corresponds to one of the majority flavors.

      std::random_device Seeder;
      std::mt19937       Engine{Seeder()};
      // Notice that these values are inclusive

      std::uniform_int_distribution Distribution{LeftSlabInclusiveIndex, RightSlabExclusiveIndex};

      std::size_t    CurrentGuessIndex{};
      std::size_t    PieceSize{RightSlabExclusiveIndex - LeftSlabInclusiveIndex};
      const uint32_t FlavorCountThreshold{static_cast<uint32_t>(std::ceil(PieceSize / 3.0))};

      std::optional<uint32_t> FirstFlavorType;
      for(; CurrentGuessIndex < NUM_GUESSES; ++CurrentGuessIndex)
      {
         const auto GuessIndex{Distribution(Engine)};
         const auto FlavorType{PieceFlavors[GuessIndex] - 1};
         const auto GuessCount{CountNumFlavoredPiecesInSlab(FlavorIndexLookup, FlavorType, LeftSlabInclusiveIndex,
                                                            RightSlabExclusiveIndex)};

         if(GuessCount >= FlavorCountThreshold)
         {
            FirstFlavorType = FlavorType;
            break;
         }
      }

      if(!FirstFlavorType)
      {
         return {};
      }

      std::optional<uint32_t> SecondFlavorType;
      for(; CurrentGuessIndex < NUM_GUESSES; ++CurrentGuessIndex)
      {
         const auto GuessIndex{Distribution(Engine)};
         const auto FlavorType{PieceFlavors[GuessIndex] - 1};

         const auto GuessCount{CountNumFlavoredPiecesInSlab(FlavorIndexLookup, FlavorType, LeftSlabInclusiveIndex,
                                                            RightSlabExclusiveIndex)};

         if(FirstFlavorType.value() == FlavorType)
         {
            if(GuessCount > FlavorCountThreshold * 2)
            {
               SecondFlavorType = FlavorType;
               break;
            }
         }
         else
         {
            if(GuessCount >= FlavorCountThreshold)
            {
               SecondFlavorType = FlavorType;
               break;
            }
         }
      }

      if(!SecondFlavorType)
      {
         return YokanResult{{FirstFlavorType.value(), -1}, YokanQueryResult::NO};
      }

      return YokanResult{{FirstFlavorType.value(), SecondFlavorType.value()}, YokanQueryResult::YES};
   }
}
