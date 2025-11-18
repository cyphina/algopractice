#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <print>
#include <ranges>
#include <vector>

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
   std::list<std::string> dictionary{"aardvark", "cat"};
   std::list<std::string> newWords{"baby", "bomb"};
   dictionary.splice(++std::cbegin(dictionary), newWords);
   std::println("{}", dictionary);
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
}
