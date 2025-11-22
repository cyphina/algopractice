#include "livingquality.h"
#include <algorithm>
#include <ranges>

namespace LivingQuality
{
   uint32_t CalculateMinimumMedianRectangle(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                            uint32_t RectHeight, Core::GridCoordinate RectangleTopLeft)
   {
      std::vector<uint32_t> RectangleValues;
      RectangleValues.reserve(RectHeight * RectWidth);

      for(int i{0}; i < RectWidth; ++i)
      {
         for(int j{0}; j < RectHeight; ++j)
         {
            Core::GridCoordinate AdjustedCoordinate{RectangleTopLeft.Row + j, RectangleTopLeft.Column + i};
            RectangleValues.push_back(CityQualityRankings[AdjustedCoordinate.Row, AdjustedCoordinate.Column].value());
         }
      }

      const size_t UpperMiddleIndex{RectangleValues.size() / 2};

      if(RectangleValues.size() % 2 == 0)
      {
         std::ranges::nth_element(RectangleValues, RectangleValues.begin() + UpperMiddleIndex);
         const auto   UpperMiddle{RectangleValues[UpperMiddleIndex]};
         const size_t LowerMiddleIndex{UpperMiddleIndex - 1};
         // Remember half open ranges.
         std::ranges::nth_element(RectangleValues.begin(), RectangleValues.begin() + LowerMiddleIndex,
                                  RectangleValues.begin() + UpperMiddleIndex);
         const auto LowerMiddle{RectangleValues[LowerMiddleIndex]};

         return (UpperMiddle + LowerMiddle) / 2;
      }
      else
      {
         std::ranges::nth_element(RectangleValues, RectangleValues.begin() + UpperMiddleIndex);
         return RectangleValues[UpperMiddleIndex];
      }
   }

   uint32_t LivingQuality::FindMinimumMedianRectangleInCityBrute(const Core::Grid<uint32_t>& CityQualityRankings,
                                                                 uint32_t RectWidth, uint32_t RectHeight)
   {
      uint32_t BestMinimumMedian{std::numeric_limits<uint32_t>::max()};
      for(size_t i{0}; i < CityQualityRankings.GetWidth() - RectWidth; ++i)
      {
         for(size_t j{0}; j < CityQualityRankings.GetHeight() - RectHeight; ++j)
         {
            const auto Median{CalculateMinimumMedianRectangle(CityQualityRankings, RectWidth, RectHeight, {j, i})};
            if(Median < BestMinimumMedian)
            {
               BestMinimumMedian = Median;
            }
         }
      }

      return BestMinimumMedian;
   }
}
