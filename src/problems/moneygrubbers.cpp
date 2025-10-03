#include <iostream>
#include <limits>
#include <print>
#include <vector>

struct MoneyGrubbersResult
{
   std::vector<int> StrategyIndices;
   int              OptimalPrice{-1};

   bool IsSet() const { return OptimalPrice > -1; }
};

struct MoneyGrubbersPricingScheme
{
   int NumThings{};
   int Price{};
};

// Moneygrubbers problem - Have to buy at least k things and get the cheapest price.
// Always assume in our pricing scheme there is an entry for buying a singular item.

using PricingSchemes = std::vector<MoneyGrubbersPricingScheme>;

MoneyGrubbersResult MoneyGrubbersSolveForValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy, std::vector<int> StrategyIndices,
                                               std::vector<MoneyGrubbersResult>& Memo)
{
   if(NumItemsToBuy == 0)
   {
      return {StrategyIndices, 0};
   }

   MoneyGrubbersResult OptimalResult{{}, std::numeric_limits<int>::max()};
   for(int i{0}; i < PricingSchemes.size(); ++i)
   {
      if(PricingSchemes[i].NumThings < NumItemsToBuy)
      {
         const auto OptimalSubproblemValue{NumItemsToBuy - PricingSchemes[i].NumThings};

         if(!Memo[OptimalSubproblemValue].IsSet())
         {
            // Result at K things you have to check K-N for each pricing schema's NumThings N.
            StrategyIndices.emplace_back(PricingSchemes[i].NumThings);
            auto SolvedResult{MoneyGrubbersSolveForValue(PricingSchemes, NumItemsToBuy - PricingSchemes[i].NumThings, StrategyIndices, Memo)};
            // From K-N optimal solution lets say we take the path to make it K. We have to pay the cost.

            Memo[OptimalSubproblemValue] = SolvedResult;
            SolvedResult.OptimalPrice += PricingSchemes[i].Price;

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
            return Memo[OptimalSubproblemValue];
         }
      }
   }

   return OptimalResult;
}

MoneyGrubbersResult MoneyGrubbersSolveForAtLeastValue(const PricingSchemes& PricingSchemes, int NumItemsToBuy)
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

   for(int i = NumItemsToBuy + 1; i < NumItemsToBuy + MaxNumThingScheme->NumThings - 1; ++i)
   {
      const auto SolvedResult{MoneyGrubbersSolveForValue(PricingSchemes, NumItemsToBuy, {}, Memo)};
      Memo[i] = SolvedResult;

      if(SolvedResult.OptimalPrice < OptimalResult.OptimalPrice)
      {
         OptimalResult = SolvedResult;
      }
   }

   return OptimalResult;
}

int main()
{
   std::println("Price For Buying One Apple - Number of Pricing Schemes");
   int OneAppleCost{}, NumPricingSchemes{};
   std::cin >> OneAppleCost >> NumPricingSchemes;

   if(std::cin)
   {
      PricingSchemes PricingSchemes;
      PricingSchemes.reserve(NumPricingSchemes + 1);
      PricingSchemes.emplace_back(1, OneAppleCost);

      for(int i{0}; i < NumPricingSchemes; ++i)
      {
         if(std::cin)
         {
            std::println("Scheme - Num Items - Price");

            MoneyGrubbersPricingScheme Scheme;
            std::cin >> Scheme.NumThings >> Scheme.Price;
         }
      }

      int AtLeastPrice{};
      while(std::cin >> AtLeastPrice)
      {
         const auto Result{MoneyGrubbersSolveForAtLeastValue(PricingSchemes, AtLeastPrice)};
      }
   }
}
