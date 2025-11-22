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
   uint32_t MinimumMedianRectangle(const Core::Grid<uint32_t>& CityQualityRankings, uint32_t RectWidth,
                                   uint32_t RectHeight);
}
