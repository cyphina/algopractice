#include "livingquality.h"
#include <algorithm>
#include <ranges>

namespace
{
   int LookupRectInRangedSumQueryGridMiddle(const Core::Grid<int>& RangedSumQueryGrid, Core::GridCoordinate TopLeft,
                                            Core::GridCoordinate BottomRight)
   {
      return RangedSumQueryGrid.At(BottomRight).value() -
             RangedSumQueryGrid.At(BottomRight.Row, TopLeft.Column - 1).value() -
             RangedSumQueryGrid.At(TopLeft.Row - 1, BottomRight.Column).value() +
             RangedSumQueryGrid.At(TopLeft.Row - 1, TopLeft.Column - 1).value();
   }
}
namespace LivingQuality
{
   uint32_t CalculateMinimumMedianRectangle(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                            uint32_t RectHeight, Core::GridCoordinate RectangleTopLeft)
   {
      std::vector<uint32_t> RectangleValues;
      RectangleValues.reserve(RectHeight * RectWidth);

      for(size_t i{0}; i < RectHeight; ++i)
      {
         for(size_t j{0}; j < RectWidth; ++j)
         {
            Core::GridCoordinate AdjustedCoordinate{RectangleTopLeft.Row + i, RectangleTopLeft.Column + j};
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

   uint32_t FindMinimumMedianRectangleInCityBrute(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                                  uint32_t RectHeight)
   {
      uint32_t BestMinimumMedian{std::numeric_limits<uint32_t>::max()};
      for(size_t i{0}; i < CityQualityRankings.GetWidth() - RectWidth; ++i)
      {
         for(size_t j{0}; j < CityQualityRankings.GetHeight() - RectHeight; ++j)
         {
            const auto Median{CalculateMinimumMedianRectangle(CityQualityRankings, RectWidth, RectHeight, {j, i})};
            BestMinimumMedian = std::min(Median, BestMinimumMedian);
         }
      }

      return BestMinimumMedian;
   }

   size_t FindMinimumMedianRectangleInCityFeasibleSlow(const Core::Grid<uint32_t>& CityQualityRankings,
                                                       uint32_t RectWidth, uint32_t RectHeight)
   {
      // All rects have median > 0.
      // Low is the value where all rectangles have median > it.
      size_t Low{0};

      // All rects have median < the number of cities
      // High is the value where all rectangles have median <= it.
      size_t High{CityQualityRankings.GetWidth() * CityQualityRankings.GetHeight()};

      // Stop if somehow the median value all rectangles are <= is somehow bleeding into the median value all rectangles is > than.
      while(High - 1 > Low)
      {
         // Mid is the test median
         size_t Mid{(Low + High) / 2};

         if(TestRectanglesFeasibleSlow(CityQualityRankings, RectWidth, RectHeight, Mid))
         {
            High = Mid;
         }
         else
         {
            Low = Mid;
         }
      }

      return High;
   }

   size_t FindMinimumMedianRectangleInCityFeasible(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                                   uint32_t RectHeight)
   {
      // All rects have median > 0.
      // Low is the value where all rectangles have median > it.
      size_t Low{0};
      // All rects have median < the number of cities
      // High is the value where all rectangles have median <= it.
      size_t High{CityQualityRankings.GetWidth() * CityQualityRankings.GetHeight()};

      // Stop if somehow the median value all rectangles are <= is somehow bleeding into the median value all rectangles is > than.
      while(High - 1 > Low)
      {
         // Mid is the test median
         size_t Mid{(Low + High) / 2};

         if(TestRectanglesFeasibleRangeSumQuery(CityQualityRankings, RectWidth, RectHeight, Mid))
         {
            High = Mid;
         }
         else
         {
            Low = Mid;
         }
      }

      return High;
   }

   bool TestRectanglesFeasibleSlow(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                   uint32_t RectHeight, uint32_t MedianThresholdGuess)
   {
      for(size_t i{0}; i < CityQualityRankings.GetHeight() - RectHeight; ++i)
      {
         for(size_t j{0}; j < CityQualityRankings.GetWidth() - RectWidth; ++j)
         {
            if(RectHeight * RectWidth % 2 != 0)
            {
               int NumItemsBelowThreshold{};
               // Odd number we can check feasibility just by seeing if our median is <= MedianThresholdGuess
               for(size_t RectRow{0}; RectRow < RectHeight; ++RectRow)
               {
                  for(size_t RectColumn{0}; RectColumn < RectWidth; ++RectColumn)
                  {
                     if(CityQualityRankings[RectRow + i, RectColumn + j] <= MedianThresholdGuess)
                     {
                        ++NumItemsBelowThreshold;
                     }
                     else
                     {
                        --NumItemsBelowThreshold;
                     }
                  }
               }

               if(NumItemsBelowThreshold > 0)
               {
                  return true;
               }
            }
            else
            {
               const uint32_t Median{
                   LivingQuality::CalculateMinimumMedianRectangle(CityQualityRankings, RectWidth, RectHeight, {i, j})};
               if(Median <= MedianThresholdGuess)
               {
                  return true;
               }
            }
         }
      }

      return false;
   }

   bool TestRectanglesFeasibleRangeSumQuery(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                            uint32_t RectHeight, uint32_t MedianThresholdGuess)
   {
      Core::Grid<int> RangeSumQueryGrid{CityQualityRankings.GetWidth(), CityQualityRankings.GetHeight()};

      // Fill up the sides first
      uint32_t Sum{};
      for(size_t i{0}; i < CityQualityRankings.GetHeight(); ++i)
      {
         Sum += CityQualityRankings[i, 0].value() > MedianThresholdGuess ? 1 : -1;
         RangeSumQueryGrid[i, 0] = Sum;
      }

      Sum = 0;
      for(size_t i{0}; i < CityQualityRankings.GetWidth(); ++i)
      {
         Sum += CityQualityRankings[0, i].value() > MedianThresholdGuess ? 1 : -1;
         RangeSumQueryGrid[0, i] = Sum;
      }

      // Fill up the 2d range sum query
      for(size_t i{1}; i < CityQualityRankings.GetHeight(); ++i)
      {
         for(size_t j{1}; j < CityQualityRankings.GetWidth(); ++j)
         {
            const auto CurrentSquareMedianSign{CityQualityRankings[i, j].value() > MedianThresholdGuess ? 1 : -1};
            RangeSumQueryGrid[i, j] = CurrentSquareMedianSign + RangeSumQueryGrid[i - 1, j].value() +
                                      RangeSumQueryGrid[i, j - 1].value() - RangeSumQueryGrid[i - 1, j - 1].value();
         }
      }

      // Note when indexing, anytime we use RectWidth/RectHeight we need to -1.
      // Do (0,0) first
      {
         const auto NumItemsAboveMedianGuess{RangeSumQueryGrid.At(RectHeight - 1, RectWidth - 1)};
         if(NumItemsAboveMedianGuess <= 0)
         {
            return true;
         }
      }

      // Then let's do the first row and column checks separately to prevent indices breaking
      for(size_t i{1}; i < CityQualityRankings.GetHeight() - RectHeight; ++i)
      {
         const auto CurrentRectangleRangedSum{RangeSumQueryGrid.At(i + RectHeight - 1, RectWidth - 1).value()};
         const auto ExcessRectangleRangedSum{RangeSumQueryGrid.At(i - 1, RectWidth - 1).value()};
         const auto NumItemsAboveMedianGuess{CurrentRectangleRangedSum - ExcessRectangleRangedSum};
         if(NumItemsAboveMedianGuess <= 0)
         {
            return true;
         }
      }

      for(size_t i{1}; i < CityQualityRankings.GetWidth() - RectWidth; ++i)
      {
         const auto CurrentRectangleRangedSum{RangeSumQueryGrid.At(RectHeight - 1, i + RectWidth - 1).value()};
         const auto ExcessRectangleRangedSum{RangeSumQueryGrid.At(RectHeight - 1, i - 1).value()};
         const auto NumItemsAboveMedianGuess{CurrentRectangleRangedSum - ExcessRectangleRangedSum};
         if(NumItemsAboveMedianGuess <= 0)
         {
            return true;
         }
      }

      // Then lets check everything in the grid
      for(size_t i{1}; i < CityQualityRankings.GetHeight() - RectHeight; ++i)
      {
         for(size_t j{1}; j < CityQualityRankings.GetWidth() - RectWidth; ++j)
         {
            const auto NumItemsAboveMedianGuess{LookupRectInRangedSumQueryGridMiddle(
                RangeSumQueryGrid, {i, j}, {i + RectHeight - 1, j + RectWidth - 1})};
            if(NumItemsAboveMedianGuess <= 0)
            {
               return true;
            }
         }
      }

      return false;
   }
}
