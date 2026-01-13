#include <chrono>
#include <cstdint>
#include <print>
#include <thread>
#include "core/DebugUtils.h"
#include "core/Grid.h"

void TestImportanceOfFalseSharing()
{
   static constexpr uint32_t TEST_MATRIX_SIZE{256};

   Core::Grid<int> Test(TEST_MATRIX_SIZE, TEST_MATRIX_SIZE);

   std::size_t Index{};
   for(std::size_t i{}; i < TEST_MATRIX_SIZE; ++i)
   {
      for(std::size_t j{}; j < TEST_MATRIX_SIZE; ++j)
      {
         Test[i, j] = Index++;
      }
   }

   {
      Profiling::ScopedTimer Timer;
      // Row major - Processes row by row
      std::size_t Sum{};
      for(std::size_t i{}; i < TEST_MATRIX_SIZE; ++i)
      {
         for(std::size_t j{}; j < TEST_MATRIX_SIZE; ++j)
         {
            Sum += Test[i, j].value();
         }
      }
   }

   {
      // Column major - Processes column by column. For large enough matrices this requires reading another cache line.
      Profiling::ScopedTimer Timer;

      std::size_t Sum2{};
      for(std::size_t i{}; i < TEST_MATRIX_SIZE; ++i)
      {
         for(std::size_t j{}; j < TEST_MATRIX_SIZE; ++j)
         {
            Sum2 += Test[j, i].value();
         }
      }
   }
}

// Avoid false tearing by making sure data written to by separate threads is not in the same cache line.
struct Counters
{
   alignas(std::hardware_constructive_interference_size) std::atomic<int> a;
   alignas(std::hardware_constructive_interference_size) std::atomic<int> b;
};

void ThreadFunction(std::stop_token Token, int Id)
{
   using namespace std::chrono;

   while(!Token.stop_requested())
   {
      std::println("Thread {} doing some work.", Id);
      std::this_thread::sleep_for(500ms);
   }
}

void TestJThread()
{
   using namespace std::chrono;

   std::jthread Job1{ThreadFunction, 1};
   std::jthread Job2{ThreadFunction, 2};

   std::this_thread::sleep_for(2s);
   std::println("main() is ending.");

   Job1.request_stop();
   Job2.request_stop();
}

int main()
{
   TestImportanceOfFalseSharing();
   TestJThread();
}
