#include "misc/snowflake.h"
#include <array>
#include <fstream>
#include <iostream>
#include <print>
#include <random>

namespace
{
   [[maybe_unused]] void GenerateRandomSnowflakeFile()
   {
      std::ofstream Out("snowflakes.txt");
      if(!Out)
      {
         std::println(std::cerr, "Could not open output file");
         return;
      }

      int NumSnowflakesToGenerate;

      std::println("Enter Number of Snowflakes to Generate:");
      if(std::cin >> NumSnowflakesToGenerate)
      {
         Out << NumSnowflakesToGenerate << "\n";

         std::random_device                 Rd;
         std::mt19937                       Gen(Rd());
         std::uniform_int_distribution<int> Dist(1, 10);

         std::vector<std::array<int, 6>> Snowflakes;
         Snowflakes.reserve(NumSnowflakesToGenerate);

         for(int i = 0; i < NumSnowflakesToGenerate; ++i)
         {
            std::array<int, 6> NewSnowflake;
            std::ranges::generate(NewSnowflake,
                                  [&]
                                  {
                                     return Dist(Gen);
                                  });
            Snowflakes.emplace_back(NewSnowflake);
         }

         for(int i = 0; i < Snowflakes.size(); ++i)
         {
            Out << Snowflakes[i][0];
            for(int j = 1; j < 6; ++j)
            {
               Out << std::format(" {}", Snowflakes[i][j]);
            }
            Out << "\n";
         }
      }
      else
      {
         std::println("Invalid Number of Snowflakes to Generate");
      }
   }

   void TestIdenticalSnowflakes()
   {
      int NumSnowflakes;
      std::println("Input number of snowflakes:");

      if(std::cin >> NumSnowflakes; !std::cin)
      {
         std::println("Bad input!");
      }

      std::vector<std::array<int, 6>> Snowflakes;
      Snowflakes.reserve(NumSnowflakes);

      for(int i = 0; i < NumSnowflakes; ++i)
      {
         std::array<int, 6> NewSnowflake;
         for(int j = 0; j < 6; ++j)
         {
            std::cin >> NewSnowflake[j];
            if(!std::cin)
            {
               std::println("Error with input");
            }
         }
         Snowflakes.emplace_back(NewSnowflake);
      }

      if(const auto SnowflakeResult{Snowflake::AreAnySnowflakesIdentical(Snowflakes)}; SnowflakeResult.IsValid())
      {
         std::println("Identical Snowflakes Found {} {}", SnowflakeResult.first.value(), SnowflakeResult.second.value());
      }
      else
      {
         std::println("Identical Snowflakes Not Found");
      }
   }
}

int main()
{
   TestIdenticalSnowflakes();
   return 0;
}
