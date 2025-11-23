#pragma once

#include <cstdint>
#include "core/Grid.h"

namespace LivingQuality
{
   /**
    * Given a grid of rankings of blocks within a city, and a rectangle size, we want to find the rectangle in the grid that has the minimum
    * "median quality rank".
    * @return 
    */
   uint32_t FindMinimumMedianRectangleInCityBrute(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                                  uint32_t RectHeight);

   size_t FindMinimumMedianRectangleInCityFeasibleSlow(const Core::Grid<uint32_t>& CityQualityRankings,
                                                       uint32_t RectWidth, uint32_t RectHeight);

   size_t FindMinimumMedianRectangleInCityFeasible(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                                   uint32_t RectHeight);

   uint32_t CalculateMinimumMedianRectangle(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                            uint32_t RectHeight, Core::GridCoordinate RectangleTopLeft);

   /**
    * Checks to see if a rectangle on the grid is feasible, aka if there's a rect with a median less than the threshold.
    * Pretty sure it breaks if we have an even number of items in our rectangle, then we'd have to handle the situation
    * when we have a tie in the number of items below above the median explicitly. So in that case I fellback to `nth_element` checks.
    */
   bool TestRectanglesFeasibleSlow(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                   uint32_t RectHeight, uint32_t MedianThresholdGuess);

   /**
    * The idea here is to use a 2d range sum query to be able to quickly figure out if the number of elements above our median in some rectangle in the grid
    * is greater than 1 or not (for odd rects). For even we'd probalby have to still compute the true median but we'll handle that later.
    */
   bool TestRectanglesFeasibleRangeSumQuery(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                            uint32_t RectHeight, uint32_t MedianThresholdGuess);
}
