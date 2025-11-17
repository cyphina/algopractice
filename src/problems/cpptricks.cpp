#include <iostream>
#include <iterator>
#include <map>
#include <mdspan>
#include <print>
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

struct TestCopyVsAssign
{
   TestCopyVsAssign() {}

   TestCopyVsAssign(std::string_view Data) : data{Data} {}

   TestCopyVsAssign(const TestCopyVsAssign& Other) : data(Other.data) { std::println("Copy Construct"); }

   TestCopyVsAssign(TestCopyVsAssign&& Other) noexcept : data(Other.data) { std::println("Move Construct"); }

   TestCopyVsAssign& operator=(const TestCopyVsAssign& Other)
   {
      std::println("Copy Assign");

      if(this == &Other)
      {
         return *this;
      }
      data = Other.data;
      return *this;
   }

   TestCopyVsAssign& operator=(TestCopyVsAssign&& Other) noexcept
   {
      std::println("Move Assign");

      if(this == &Other)
      {
         return *this;
      }

      data = Other.data;
      return *this;
   }

   [[nodiscard]] bool operator==(const TestCopyVsAssign& Other) const  = default;
   [[nodiscard]] auto operator<=>(const TestCopyVsAssign& Other) const = default;

   std::string data;
};

void InsertMapAndPrint()
{
   using namespace std::literals;

   std::map<TestCopyVsAssign, int> DataMap{{"wee"sv, 2}, {"pee"sv, 3}, {"dee"sv, 5}};
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
   for(const std::pair<TestCopyVsAssign, int>& elem : DataMap)
   {
      std::println("{} {}", elem.first.data, elem.second);
   }

   auto Start{DataMap.begin()};
   std::advance(Start, 2);
   DataMap.erase(Start, DataMap.end());
   std::println("Size: {}", DataMap.size());
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
   TestMdSpan();
   InsertMapAndPrint();
}
