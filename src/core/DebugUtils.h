#pragma once
#include <cassert>

#if defined(_MSC_VER)
#   define debug_break() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#   include <csignal>
#   define debug_break() raise(SIGTRAP)
#else
#   define debug_break() ((void)0)
#endif

// Function call is just an expression so we use a comma expression to return only the second part and still invoke the function's side effect.

#ifdef _DEBUG
#   define ensure(cond) ((cond) ? true : (debug_break(), false))
#else
#   define ensure(cond) (cond)
#endif

#define PRE_RETURN(cond, retval) \
   if(!ensure(cond))             \
   {                             \
      return retval;             \
   }

#include <chrono>
#include <concepts>
#include <print>
#include <random>
#include <ranges>

namespace Profiling
{
   class ScopedTimer
   {
    public:
      ScopedTimer() { startTime = std::chrono::high_resolution_clock::now(); }

      ~ScopedTimer()
      {
         const auto EndTime{std::chrono::high_resolution_clock::now()};
         const auto Duration{EndTime - startTime};
         std::println("Time Elapsed: {}", Duration.count());
      }

      std::chrono::high_resolution_clock::time_point startTime;
   };
}

namespace Test
{
   /**
    * Fills up a vector with elements [0, N) shuffled. 
    */
   template <std::integral T>
   std::vector<T> RandomFillIntVec(int Size)
   {
      std::vector<T>             Values{std::from_range, std::views::iota(0, Size)};
      std::random_device         Seeder;
      std::default_random_engine Generator{Seeder()};

      std::ranges::shuffle(Values, Generator);

      return Values;
   }

   template <std::ranges::input_range RangeT>
   void PrintRange(RangeT Range)
   {
      std::print("[");

      auto It{Range.begin()};

      if(!Range.empty())
      {
         std::print("{}" << *It);
         ++It;
      }
      for(; It != Range.end(); ++It)
      {
         std::print(", {}", *It);
      }
      std::print("]");
   }

}
