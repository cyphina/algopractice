#pragma once

#include <compare>
#include <cstdint>
#include <vector>

namespace SupermarketPromotion
{
   struct Receipt
   {
      uint32_t price{};
      size_t   index{};

      [[nodiscard]] bool                 operator==(const Receipt& OtherReceipt) const  = default;
      [[nodiscard]] std::strong_ordering operator<=>(const Receipt& OtherReceipt) const = default;
   };

   /**
    * Find min and max receipts after each day and then prize gets added by max - min.
    * Remove the max and min ballot.
    * Repeat.
    * Returns total prize over all the days
    *
    * INVARIANT - At least 2 ballots in the box at all times.
    */
   uint32_t SupermarketProblem(std::vector<std::vector<uint32_t>> DailyReceiptPrices);
}
