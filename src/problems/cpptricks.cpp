#include <iostream>
#include <iterator>
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
}
