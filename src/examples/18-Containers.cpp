#include <functional>
#include <unordered_map>

// Hash to leverage across every usage by default in the program.
template <>
struct std::hash<std::pair<int, int>>
{
   size_t operator()(const std::pair<int, int>& Value) const noexcept
   {
      return std::hash<int>{}(Value.first + Value.second);
   }
};

namespace
{
   // Pass to specific map.
   struct PairHash
   {
      size_t operator()(const std::pair<int, int>& p) const noexcept
      {
         return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
      }
   };

   void TestCustomHashFunction()
   {
   }

   void TestAssociativeContainerOperations()
   {
   }
}

int main()
{
}
