#include "AtLeastKnapsack.h"

namespace AtLeastKnapsack
{
   MoneyGrubbersResult AtLeastKnapsack::MoneyGrubbersSolveForValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy,
                                                                   std::vector<int> StrategyIndices, std::vector<MoneyGrubbersResult>& Memo)
   {
      if(NumItemsToBuy == 0)
      {
         return {StrategyIndices, 0};
      }

      MoneyGrubbersResult OptimalResult{{}, std::numeric_limits<float>::max()};
      for(int i{0}; i < PricingSchemes.size(); ++i)
      {
         if(PricingSchemes[i].NumThings <= NumItemsToBuy)
         {
            const auto OptimalSubproblemValue{NumItemsToBuy - PricingSchemes[i].NumThings};

            if(!Memo[OptimalSubproblemValue].IsSet())
            {
               // Result at K things you have to check K-N for each pricing schema's NumThings N.
               StrategyIndices.emplace_back(PricingSchemes[i].NumThings);
               auto SolvedResult{MoneyGrubbersSolveForValue(PricingSchemes, NumItemsToBuy - PricingSchemes[i].NumThings, StrategyIndices, Memo)};
               // From K-N optimal solution lets say we take the path to make it K. We have to pay the cost.

               SolvedResult.OptimalPrice.value() += PricingSchemes[i].Price;
               SolvedResult.StrategyIndices.emplace_back(PricingSchemes[i].NumThings);

               if(SolvedResult.OptimalPrice < OptimalResult.OptimalPrice)
               {
                  OptimalResult = SolvedResult;
               }

               // We might be able to do another loop and check values NumItemsToBuy + PricingSchemes[i].NumThings if it's greater than NumItemsToBuy to solve the at least problem.
               // But I mean in the recursion we end up having to check NumItemsToBuy-1, NumItemToBuy-2 so if we did try to test out the space of buying strategies that have
               // more items we'd end up testing NumItemsToBuy+1, NumItemsToBuy+2 so we can just do this in a separate loop.
            }
            else
            {
               auto SolvedResult{Memo[OptimalSubproblemValue]};
               SolvedResult.StrategyIndices.emplace_back(PricingSchemes[i].NumThings);
               SolvedResult.OptimalPrice.value() += PricingSchemes[i].Price;

               if(SolvedResult.OptimalPrice < OptimalResult.OptimalPrice)
               {
                  OptimalResult = SolvedResult;
               }
            }
         }
      }

      if(!Memo[NumItemsToBuy].IsSet())
      {
         Memo[NumItemsToBuy] = OptimalResult;
      }

      return OptimalResult;
   }

   MoneyGrubbersResult AtLeastKnapsack::MoneyGrubbersSolveForAtLeastValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy)
   {
      if(PricingSchemes.empty())
      {
         return {};
      }

      const auto MaxNumThingScheme{std::ranges::max_element(PricingSchemes, {},
                                                            [](const MoneyGrubbersPricingScheme& Scheme)
                                                            {
                                                               return Scheme.NumThings;
                                                            })};

      std::vector<MoneyGrubbersResult> Memo;
      Memo.resize(NumItemsToBuy + MaxNumThingScheme->NumThings + 1);
      Memo[0] = {.OptimalPrice = 0};

      MoneyGrubbersResult OptimalResult{MoneyGrubbersSolveForValue(PricingSchemes, NumItemsToBuy, {}, Memo)};

      for(int NumItemsToLookaheadIndex = NumItemsToBuy + 1; NumItemsToLookaheadIndex < NumItemsToBuy + MaxNumThingScheme->NumThings - 1;
          ++NumItemsToLookaheadIndex)
      {
         const auto SolvedResult{MoneyGrubbersSolveForValue(PricingSchemes, NumItemsToLookaheadIndex, {}, Memo)};
         Memo[NumItemsToLookaheadIndex] = SolvedResult;

         if(SolvedResult.OptimalPrice < OptimalResult.OptimalPrice)
         {
            OptimalResult = SolvedResult;
         }
      }

      return OptimalResult;
   }
}
