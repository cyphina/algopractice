#include "RopeClimb.h"

#include <queue>
#include <ranges>
#include <vector>

namespace
{
   enum class RopeClimbState : uint8_t
   {
      Jumping,
      Falling,
   };

   struct RopeClimbNode
   {
      uint32_t                   Index;
      RopeClimbState             State;
      RopeClimb::RopeSegmentCost Cost;
   };
}

namespace RopeClimb
{
   /**
    * Can only jump up by JumpHeight. Can fall any amount. Each action is one move. Find min jumps to reach target segment index if we can.
    * PoweredSegments means you can hit that segment when climbing or falling.
    * @param JumpHeight 
    * @param TargetSegmentIndex 
    * @param PowderedSegmentIndices - Indices of every segment that has powder on it.
    * @return Minimum number of jumps required to arrive to the target segment or further on.
    */
   std::optional<RopeSegmentCost> RopeClimb(uint32_t JumpHeight, uint32_t TargetSegmentIndex,
                                            const std::unordered_set<uint32_t>& PowderedSegmentIndices)
   {
      if(JumpHeight == 0)
      {
         return {};
      }

      if(TargetSegmentIndex == 0)
      {
         return RopeSegmentCost{0, {0}};
      }

      if(PowderedSegmentIndices.contains(JumpHeight))
      {
         return {};
      }

      // BFS to search the state space.
      // We don't need a graph - we just need to be able to explore the states in a breadth first manner.
      // We could use 0-1 bfs on a graph with optimized links but we'll just instead explore using states.

      // Some segments (like powdered ones) won't have a best cost.

      using BestSegmentCostVector = std::vector<std::optional<RopeSegmentCost>>;
      BestSegmentCostVector BestSegmentCosts;

      // Need to check up to JumpHeight + TargetSegmentIndex since maybe jumping higher takes less moves depending on the setup. Or maybe we can only reach higher.
      const uint32_t HeightLimit{JumpHeight + TargetSegmentIndex};
      BestSegmentCosts.resize(HeightLimit);

      std::queue<RopeClimbNode> RopeClimbNodes;

      BestSegmentCosts[0] = {.Value = 0, .IndexHistory = {0}};
      RopeClimbNodes.push({0, RopeClimbState::Jumping, BestSegmentCosts[0].value()});

      const auto MakeNewCostIfSegmentValid =
          [](uint32_t IndexToVisit, const RopeSegmentCost& CurrentCost,
             const std::unordered_set<uint32_t>& CheckedPowderedSegmentIndices) -> std::optional<RopeSegmentCost>
      {
         const auto NewCostValue{CurrentCost.Value + 1};

         if(CheckedPowderedSegmentIndices.contains(IndexToVisit))
         {
            return {};
         }

         std::vector NewIndexHistory{CurrentCost.IndexHistory};
         NewIndexHistory.emplace_back(IndexToVisit);

         return RopeSegmentCost{NewCostValue, std::move(NewIndexHistory)};
      };

      const auto TryUpdateBestCostForSegement = [](uint32_t IndexToVisit, const RopeSegmentCost& NewSegmentCost,
                                                   BestSegmentCostVector& CheckedBestSegmentCosts)
      {
         const auto NewCostValue{NewSegmentCost.Value};

         if(CheckedBestSegmentCosts[IndexToVisit].has_value() &&
            CheckedBestSegmentCosts[IndexToVisit].value().Value <= NewCostValue)
         {
            return false;
         }

         CheckedBestSegmentCosts[IndexToVisit] = NewSegmentCost;
         return true;
      };

      while(!RopeClimbNodes.empty())
      {
         const auto& CurrentRopeClimpNode{RopeClimbNodes.front()};

         RopeClimbNodes.pop();

         const auto CurrentCost{BestSegmentCosts[CurrentRopeClimpNode.Index].value()};
         const auto CurrentIndex{CurrentRopeClimpNode.Index};

         const uint32_t NewJumpIndex{CurrentIndex + JumpHeight};
         const bool     IsNewJumpBelowTarget{NewJumpIndex < TargetSegmentIndex};

         switch(CurrentRopeClimpNode.State)
         {
            case RopeClimbState::Jumping:
            {
               if(const auto NewJumpCost{MakeNewCostIfSegmentValid(NewJumpIndex, CurrentCost, PowderedSegmentIndices)})
               {
                  if(TryUpdateBestCostForSegement(NewJumpIndex, NewJumpCost.value(), BestSegmentCosts))
                  {
                     if(IsNewJumpBelowTarget)
                     {
                        RopeClimbNodes.push({NewJumpIndex, RopeClimbState::Jumping, NewJumpCost.value()});
                     }
                     else
                     {
                        continue;
                     }
                  }

                  // Only can fall after we jumped
                  for(uint32_t FallIndex = 0; FallIndex < NewJumpIndex; ++FallIndex)
                  {
                     if(const auto NewFallCost{
                            MakeNewCostIfSegmentValid(FallIndex, NewJumpCost.value(), PowderedSegmentIndices)})
                     {
                        if(TryUpdateBestCostForSegement(FallIndex, NewFallCost.value(), BestSegmentCosts))
                        {
                           RopeClimbNodes.push({FallIndex, RopeClimbState::Falling, std::move(NewFallCost.value())});
                        }
                     }
                  }
               }
               break;
            }
            case RopeClimbState::Falling:
            {
               // Since we're checking every fall distance we don't need to keep falling since this part of checking everything below
               if(const auto NewCost{MakeNewCostIfSegmentValid(NewJumpIndex, CurrentCost, PowderedSegmentIndices)})
               {
                  if(TryUpdateBestCostForSegement(NewJumpIndex, NewCost.value(), BestSegmentCosts))
                  {
                     if(IsNewJumpBelowTarget)
                     {
                        RopeClimbNodes.push({NewJumpIndex, RopeClimbState::Jumping, std::move(NewCost.value())});
                     }
                  }
               }
               break;
            }
         }
      }
      auto ValidCosts{BestSegmentCosts | std::views::filter(
                                             [](const BestSegmentCostVector::value_type& Cost)
                                             {
                                                return Cost.has_value();
                                             })};
      auto ValidCostsToCheck{ValidCosts | std::views::drop(TargetSegmentIndex - 1)};

      if(!ValidCostsToCheck.empty())
      {
         const auto MinCost{std::ranges::min(ValidCostsToCheck)};
         return MinCost;
      }
      return {};
   }

   bool RopeSegmentCost::operator==(const RopeSegmentCost& Rhs) const
   {
      return Value == Rhs.Value;
   }

   std::strong_ordering RopeSegmentCost::operator<=>(const RopeSegmentCost& Rhs) const
   {
      return Value <=> Rhs.Value;
   }
}
