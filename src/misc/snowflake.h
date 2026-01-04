#pragma once
#include <cassert>
#include <functional>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <vector>
#include "core/MathUtil.h"

namespace Snowflake
{
   template <int N>
   using SnowflakeArray = std::array<int, N>;

   template <int N>
   bool IsIdenticalRight(const SnowflakeArray<N>& Left, const SnowflakeArray<N>& Right, int Start)
   {
      assert(Start < N);

      for(int i{}; i < N; ++i)
      {
         if(Left[i] != Right[(Start + i) % N])
         {
            return false;
         }
      }

      return true;
   }

   template <int N>
   bool IsIdenticalLeft(const SnowflakeArray<N>& Left, const SnowflakeArray<N>& Right, int Start)
   {
      assert(Start < N);

      for(int i{}; i < N; ++i)
      {
         if(Left[i] != Right[MathUtil::Wrap(Start - i, N)])
         {
            return false;
         }
      }

      return true;
   }

   template <int N>
   bool IsIdentical(const SnowflakeArray<N>& Left, const SnowflakeArray<N>& Right)
   {
      for(int Start = 0; Start < N; ++Start)
      {
         if(IsIdenticalRight(Left, Right, Start))
         {
            return true;
         }
         else if(IsIdenticalLeft(Left, Right, Start))
         {
            return true;
         }
      }
      return false;
   }

   template <int N>
   struct SnowflakeIdenticalResult
   {
      std::optional<SnowflakeArray<N>> first;
      std::optional<SnowflakeArray<N>> second;

      bool IsValid() const { return first.has_value() && second.has_value(); }
   };

   template <int N>
   SnowflakeIdenticalResult<N> AreAnySnowflakesIdenticalSlow(const std::vector<SnowflakeArray<N>>& Snowflakes)
   {
      for(int i = 0; i < Snowflakes.size(); ++i)
      {
         for(int j = i + 1; j < Snowflakes.size(); ++j)
         {
            if(IsIdentical(Snowflakes[i], Snowflakes[j]))
            {
               return {Snowflakes[i], Snowflakes[j]};
            }
         }
      }

      return {};
   }

   template <int N>
   SnowflakeIdenticalResult<N> AreAnySnowflakesIdentical(const std::vector<SnowflakeArray<N>>& Snowflakes)
   {
      using BinType = std::unordered_map<int, std::vector<SnowflakeArray<N>>>;
      BinType SnowflakeBins;

      for(int i = 0; i < Snowflakes.size(); ++i)
      {
         const int Sum{std::accumulate(cbegin(Snowflakes[i]), cend(Snowflakes[i]), 0, std::plus<>{})};
         std::vector<SnowflakeArray<N>>& Bin{SnowflakeBins[Sum]};
         Bin.emplace_back(Snowflakes[i]);
      }

      for(const typename BinType::value_type& Bin : SnowflakeBins)
      {
         const auto Result{AreAnySnowflakesIdenticalSlow(Bin.second)};
         if(Result.IsValid())
         {
            return Result;
         }
      }

      return {};
   }
}
