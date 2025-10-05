#include <optional>
#include <print>
#include <vector>

namespace AtLeastKnapsack
{
   struct MoneyGrubbersResult
   {
      std::vector<int>     StrategyIndices;
      std::optional<float> OptimalPrice{};

      bool IsSet() const { return OptimalPrice.has_value(); }
   };

   struct MoneyGrubbersPricingScheme
   {
      int   NumThings{};
      float Price{};
   };

   // Moneygrubbers problem - Have to buy at least k things and get the cheapest price.
   // Always assume in our pricing scheme there is an entry for buying a singular item.

   using PricingSchemes = std::vector<MoneyGrubbersPricingScheme>;

   MoneyGrubbersResult MoneyGrubbersSolveForValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy, std::vector<int> StrategyIndices,
                                                  std::vector<MoneyGrubbersResult>& Memo);

   MoneyGrubbersResult MoneyGrubbersSolveForAtLeastValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy);
}
