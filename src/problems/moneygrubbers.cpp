#include <iostream>
#include "memoization/AtLeastKnapsack.h"

int main()
{
   std::println("Price For Buying One Apple - Number of Pricing Schemes");
   float OneAppleCost{};
   int   NumPricingSchemes{};

   std::cin >> OneAppleCost >> NumPricingSchemes;

   if(std::cin)
   {
      AtLeastKnapsack::PricingSchemes PricingSchemes;
      PricingSchemes.reserve(NumPricingSchemes + 1);
      PricingSchemes.emplace_back(1, OneAppleCost);

      for(int i{0}; i < NumPricingSchemes; ++i)
      {
         if(std::cin)
         {
            std::println("Scheme - Num Items - Price");

            AtLeastKnapsack::MoneyGrubbersPricingScheme Scheme;
            std::cin >> Scheme.NumThings >> Scheme.Price;
            PricingSchemes.push_back(std::move(Scheme));
         }
      }

      std::println("Enter number of items to at least buy ");
      int AtLeastItems{};
      while(std::cin >> AtLeastItems)
      {
         const auto Result{MoneyGrubbersSolveForAtLeastValue(PricingSchemes, AtLeastItems)};
         std::println("Result: Optimal Price {} StrategyIndices {}", Result.OptimalPrice.value(), Result.StrategyIndices);
      }
   }

   return 0;
}
