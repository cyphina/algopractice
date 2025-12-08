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
    * Might be a good idea to pass callbacks via std::ref to STL algorithms to prevent them from being copied.
    * If they're large enough for it to matter.
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

   void TestFindAlgorithms()
   {
      std::vector<int> Data{0, 2, 4, 10, 20};
      std::vector<int> ThingsToFind{-3, -5, -10, -20};

      const auto Pred{[](int A, int B)
                      {
                         return std::abs(A) == std::abs(B);
                      }};

      const auto ResultIter{std::ranges::find_first_of(Data, ThingsToFind, Pred)};

      if(ResultIter != Data.end())
      {
         std::println("Find First Of - {}", *ResultIter);
      }

      const auto SubsequenceToMatch{ThingsToFind | std::views::drop(2)};

      const auto ResultRng{std::ranges::find_end(Data, SubsequenceToMatch, Pred)};
      const auto ResultIt2{
          std::find_end(Data.begin(), Data.end(), SubsequenceToMatch.begin(), SubsequenceToMatch.end(), Pred)};

      std::println("Find End - {}", ResultRng);
      std::println("Find End (It Version) - {}", std::ranges::subrange(ResultIt2, Data.end()));

      constexpr std::string_view TestSequence{"1001011010001"};
      constexpr auto             ResultRng2{std::ranges::search_n(TestSequence, 3, '0')};
      std::println("Search N - First Sequence of 3 0s {}", ResultRng2);
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

   void TestModifyingSequence()
   {
      std::vector<int> Values(10);
      int              Index{};
      std::ranges::generate(Values,
                            [&Index]
                            {
                               ++Index;
                               return Index;
                            });
      std::println("Generate - {}", Values);

      std::ranges::transform(Values, Values.begin(),
                             [](const int& SourceValue)
                             {
                                return SourceValue + 24;
                             });

      std::println("Transform - {}", Values);

      std::vector<int> Values2(std::from_range, std::views::iota(5, 20));
      std::ranges::transform(Values, Values2, Values2.begin(),
                             [](const int& SourceValue, const int& DestinationValue)
                             {
                                return SourceValue + DestinationValue;
                             });
      std::println("Transform Binary - {}", Values2);
   }

   void TestBinarySearch()
   {
      std::vector<int> Values{2, 4, 3, 9, 3, 1'000, 55, 24, 78};
      std::ranges::sort(Values);

      auto Iter{std::ranges::lower_bound(Values, 10)};
      Values.insert(Iter, 10);

      auto Iter2{std::ranges::lower_bound(Values, 1'203)};
      Values.insert(Iter2, 1'203);

      std::println("Sorted Vector Add - {}", Values);
   }

   void TestScanAlgorithms()
   {
      std::vector<int> Data{1, 2, 3, 4};
      std::vector<int> Dest(4);
      std::inclusive_scan(Data.begin(), Data.end(), Dest.begin());
      std::println("Inclusive Scan - {}", Dest);
      std::exclusive_scan(Data.begin(), Data.end(), Dest.begin(), 0);
      std::println("Exclusive Scan - {}", Dest);

      struct TestStruct
      {
         int data{};
      };
      std::vector<TestStruct> NewData{{1}, {2}, {3}, {4}};
      std::transform_inclusive_scan(NewData.begin(), NewData.end(), Dest.begin(), std::plus<>{},
                                    [](const TestStruct& Elem)
                                    {
                                       return Elem.data * 2;
                                    });
      std::println("Inclusive Transform Scan - {}", Dest);
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
   TestFindAlgorithms();
   TestSearchSubsequenceForPattern();
   TestLexicographicalCompare();
   TestUniformContainerErasure();
   TestParallelAlgorithms();
   TestModifyingSequence();
   TestSorting();
   TestBinarySearch();
   TestScanAlgorithms();
}
