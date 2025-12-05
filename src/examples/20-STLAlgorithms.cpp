#include <algorithm>
#include <execution>
#include <functional>
#include <print>
#include "core/DebugUtils.h"

namespace
{

   class Add
   {
    public:
      static int operator()(int A, int B) { return A + B; }
   };

   template <std::input_iterator Iter, std::copy_constructible StartValueType,
             std::invocable<const StartValueType&, const StartValueType&> Operation>
   auto AccumulateData(Iter Begin, Iter End, const StartValueType& StartValue, Operation Op)
   {
      auto Accumulated{StartValue};
      for(Iter iter{Begin}; iter != End; ++iter)
      {
         Accumulated = Op(Accumulated, *iter);
      }
      return Accumulated;
   }

   void TestStaticFunctor()
   {
      const std::vector Test{3, 5, 8, 10};
      const auto        Result{AccumulateData(std::cbegin(Test), std::cend(Test), 20, &Add::operator())};
      const auto        Result2{AccumulateData(std::cbegin(Test), std::cend(Test), 20,
                                               [](int A, int B) static
                                               {
                                           return A + B;
                                        })};
      std::println("{0} {1}", Result, Result2);
   }

   /**
 * Might be a good idea to pass callbacks via std::ref to STL algorithms to prevent them from being copied:
 */
   void TestCallbackCopying()
   {
      auto MutableCallback{[Count = 0](int i) mutable
                           {
                              std::println("{}", ++Count);
                              return i > 10;
                           }};

      std::println("Callback Size {}", sizeof(MutableCallback));

      std::vector<int> Vec{5, 10, 12, 7, 8};
      if(const auto It{std::ranges::find_if(std::as_const(Vec), MutableCallback)}; It != Vec.end())
      {
         std::println("{}", *It);
      }

      std::println("Original Callback Not Incremented!");
      MutableCallback(6);

      std::println("Using std::ref!");
      if(const auto It{std::ranges::find_if(std::as_const(Vec), std::ref(MutableCallback))}; It != Vec.end())
      {
         std::println("{}", *It);
      }

      std::println("Original Callback Is Incremented");
      MutableCallback(8);
   }

   void TestLexicographicalCompare()
   {
      std::vector<int> Vec{5, 10, 12, 7, 8};
      std::vector<int> Vec2{5, 10, 12, 7, 8, 11};

      const auto Result{std::lexicographical_compare_three_way(Vec.begin(), Vec.end(), Vec2.begin(), Vec2.end())};
      if(Result == std::strong_ordering::less)
      {
         std::println("Less... well not enough elements");
      }
   }

   void TestSearchSubsequenceForPattern()
   {
      std::string               Text{"This is the haystack to search a needle in."};
      std::string               ToSearchFor{"needle"};
      std::boyer_moore_searcher Searcher{std::cbegin(ToSearchFor), std::cend(ToSearchFor)};

      auto Result{std::search(std::cbegin(Text), std::cend(Text), Searcher)};

      if(Result != std::cend(Text))
      {
         std::println("Found the needle!");
      }
   }

   void TestUniformContainerErasure()
   {
      std::vector<int> V{1, 2, 3, 4, 5, 6};
      std::erase_if(V,
                    [](int Val) static
                    {
                       return Val % 2 == 0;
                    });
      std::println("{}", V);
   }

   void TestSorting()
   {
      auto Data{Test::RandomFillIntVec<uint32_t>(30)};
      std::println("Data {}", Data);
      // Transparent comparator. Custom pred lets us describe what values should be first (greater values first).
      std::ranges::sort(Data, std::greater<>{});
      std::println("Sorted Data {}", Data);
   }

   void TestParallelAlgorithms()
   {
      std::vector Data(1'000'000, 1);

      {
         Profiling::ScopedTimer ScopedTimer;

         // Sequential
         std::for_each(std::execution::seq, Data.begin(), Data.end(),
                       [](int& x)
                       {
                          x *= 2;
                       });
      }

      {
         Profiling::ScopedTimer ScopedTimer;

         // Parallel (multi-threaded)
         std::for_each(std::execution::par, Data.begin(), Data.end(),
                       [](int& x)
                       {
                          x *= 2;
                       });
      }

      {
         Profiling::ScopedTimer ScopedTimer;

         // Parallel + Vectorized
         std::for_each(std::execution::par_unseq, Data.begin(), Data.end(),
                       [](int& x)
                       {
                          x *= 2;
                       });
      }

      std::println("{}", Data | std::ranges::views::take(20));
   }
}

int main()
{
   TestStaticFunctor();
   TestCallbackCopying();
   TestSearchSubsequenceForPattern();
   TestLexicographicalCompare();
   TestUniformContainerErasure();
   TestParallelAlgorithms();
   TestSorting();
}
