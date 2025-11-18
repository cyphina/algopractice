#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <mdspan>
#include <numeric>
#include <print>
#include <ranges>
#include <source_location>
#include <vector>
#include "core/TestUtils.h"

void CleanupVectorMemory(std::vector<int>& V)
{
   std::println("Size {} Capacity {}", V.size(), V.capacity());
   std::vector<int> Empty;
   // Cleanup all the memory after next statement.
   std::vector<int>().swap(Empty);
   std::println("Size {} Capacity {}", V.size(), V.capacity());
}

void PrintVectorOutputIterator(const std::vector<int>& Values)
{
   std::ranges::copy(std::cbegin(Values), std::cend(Values), std::ostream_iterator<int>{std::cout, " "});
   std::cout << std::endl;
}

void ReverseIteratorTest()
{
   using namespace std;
   vector myVector{11, 22, 33, 22, 11};
   auto   it{std::find(begin(myVector), end(myVector), 22)};
   auto   it2{std::find(rbegin(myVector), rend(myVector), 22)};

   if(it != myVector.end() && it2 != myVector.rend())
   {
      std::println("Found {} at {} and {} at {}", *it, distance(begin(myVector), it), *it2,
                   distance(begin(myVector), --it2.base()));
   }
}

template <typename T>
void Print3Dmdspan(const T& mdSpan)
{
   for(size_t i{0}; i < mdSpan.extents().extent(0); ++i)
   {
      for(size_t j{0}; j < mdSpan.extents().extent(1); ++j)
      {
         for(size_t k{0}; k < mdSpan.extents().extent(2); ++k)
         {
            std::print("{} ", mdSpan[i, j, k]);
         }
         std::println("");
      }
      std::println("");
   }
}

void TestMdSpan()
{
   // Some ideas from https://alexsyniakov.com/2025/04/26/c23-mdspan/
   std::vector<int> Data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
   //std::layout_stride::mapping                                   mapping{shape, std::array{dim2, 1uz}};
   //std::mdspan<int, std::extents<int, 2, 8>, std::layout_stride> data2D{data.data(), 2, 4};

   std::mdspan<int, std::extents<std::size_t, 4, 3, 2>> Data3D{Data.data(), 4, 3, 2};
   Print3Dmdspan(Data3D);
}

void InsertMapAndPrint()
{
   using namespace std::literals;

   std::map<TestUtils::TestCopyVsAssign, int> DataMap{{"wee"sv, 2}, {"pee"sv, 3}, {"dee"sv, 5}};
   if(auto Ret{DataMap.insert({"wee"sv, 33})}; Ret.second)
   {
      std::println("Insert {} succeeded", Ret.first->second);
   }

   // Needs default constructor for this!
   DataMap["zee"sv] = 39;

   // Ok
   for(auto& [key, data] : DataMap)
   {
      std::println("{} {}", key.data, data);
   }

   // Ok
   for(const auto& [key, data] : DataMap)
   {
      std::println("{} {}", key.data, data);
   }

   std::println("Extra Copies!!!");

   // Copying!!!
   // ReSharper disable once CppRangeBasedForIncompatibleReference
   for(const std::pair<TestUtils::TestCopyVsAssign, int>& elem : DataMap)
   {
      std::println("{} {}", elem.first.data, elem.second);
   }

   auto Start{DataMap.begin()};
   std::advance(Start, 2);
   DataMap.erase(Start, DataMap.end());
   std::println("Size: {}", DataMap.size());
}

template <std::ranges::input_range T>
constexpr auto ModifiedAvg(const T& rg)
{
   using elemType = std::ranges::range_value_t<T>;
   std::vector<elemType> v{std::ranges::begin(rg), std::ranges::end(rg)};
   v.push_back(elemType{});
   std::ranges::sort(v);
   auto newEnd = std::unique(v.begin(), v.end());
   auto sum    = std::accumulate(v.begin(), newEnd, elemType{});
   return sum / static_cast<double>(v.size());
}

void PrintCompileTimeAvg()
{
   // Use array instead of vec here so we can set it up via aggregate initialization
   constexpr std::array Orig{0, 8, 15, 132, 4, 77};
   constexpr auto       Avg{ModifiedAvg(Orig)};
   std::println("Average: {}", Avg);
}

void EraseIf()
{
   std::vector Vec{std::views::iota(0, 10) | std::ranges::to<std::vector<int>>()};
   auto        Erased{std::erase_if(Vec,
                                    [](int elem)
                                    {
                                return elem % 2 == 0;
                             })};
   std::println("{} {}", Vec, Erased);
}

void Splice()
{
   std::list<std::string> Dictionary{"aardvark", "cat"};
   std::list<std::string> NewWords{"baby", "bomb"};
   Dictionary.splice(++std::cbegin(Dictionary), NewWords);
   std::println("{}", Dictionary);
}

double SafeDivide(double Num, double Den)
{
   if(Den == 0)
   {
      throw std::invalid_argument{"Divide By Zero!"};
   }
   return Num / Den;
}

void TestException()
{
   try
   {
      std::println("{}", SafeDivide(5, 2));
      std::println("{}", SafeDivide(10, 0));
   }
   catch(const std::invalid_argument& E)
   {
      std::println("Caught exceptionm: {}", E.what());
   }

   std::println("Yo Momma");
}

class please_terminate_me : public std::bad_alloc
{
};

void MyNewHandler()
{
   std::println(std::cerr, "Unable to allocate memory.");
   throw please_terminate_me{};
}

void TestMemoryExceptionHandler()
{
   try
   {
      std::new_handler OldHandler{std::set_new_handler(MyNewHandler)};
      size_t           NumInts{std::numeric_limits<size_t>::max()};
      int*             Ptr{new int[NumInts]};
      std::set_new_handler(OldHandler);
   }
   catch(const please_terminate_me& E)
   {
      auto Location{std::source_location::current()};
      std::println(std::cerr, "{}({}): Unable to allocate memory: {}", Location.file_name(), Location.line(), E.what());
      std::println("Terminating Program!");
      return;
   }
}

int main()
{
   std::vector<int> Values;
   Values.reserve(500);
   for(int i = 0; i < 100; ++i)
   {
      Values.push_back(i);
   }

   PrintVectorOutputIterator(Values);
   ReverseIteratorTest();
   CleanupVectorMemory(Values);
   PrintCompileTimeAvg();
   EraseIf();
   Splice();
   TestMdSpan();
   InsertMapAndPrint();
   TestException();
   TestMemoryExceptionHandler();
}
