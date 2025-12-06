#include "supermarketPromotion.h"
#include <unordered_set>
#include "core/Heap.h"

namespace SupermarketPromotion
{
   uint32_t SupermarketProblem(std::vector<std::vector<uint32_t>> DailyReceiptPrices)
   {
      std::unordered_set<uint32_t>     PrizeReceiptIndices;
      Heap::Heap<Receipt, std::less<>> MaxReceipts;
      Heap::Heap<Receipt>              MinReceipts;
      uint32_t                         PrizeSum{};
      size_t                           ReceiptIndex{};

      for(size_t i{0}; i < DailyReceiptPrices.size(); ++i)
      {
         for(const auto& ReceiptPrice : DailyReceiptPrices[i])
         {
            Receipt NewReceipt{.price = ReceiptPrice, .index = ReceiptIndex};
            MaxReceipts.Insert(NewReceipt);
            MinReceipts.Insert(NewReceipt);
         }

         if(MaxReceipts.IsEmpty())
         {
            continue;
         }
         else
         {
            auto MostExpensiveReceipt{MaxReceipts.ExtractTop()};
            while(PrizeReceiptIndices.contains(MostExpensiveReceipt.index))
            {
               if(!MaxReceipts.IsEmpty())
               {
                  MostExpensiveReceipt = MaxReceipts.ExtractTop();
               }
               else
               {
                  MostExpensiveReceipt = {};
               }
            }

            PrizeSum += MostExpensiveReceipt.price;
         }

         if(!MinReceipts.IsEmpty())
         {
            auto LeastExpensiveReceipt{MinReceipts.ExtractTop()};

            while(PrizeReceiptIndices.contains(LeastExpensiveReceipt.index))
            {
               if(!MinReceipts.IsEmpty())
               {
                  LeastExpensiveReceipt = MinReceipts.ExtractTop();
               }
               else
               {
                  LeastExpensiveReceipt = {};
               }
            }

            PrizeSum -= LeastExpensiveReceipt.price;
         }
      }

      return PrizeSum;
   }
}
