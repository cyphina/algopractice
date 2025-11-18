#pragma once
#include <print>
#include <string_view>

namespace TestUtils
{
   /**
    * A wrapper class you can use to test whether copying or assignments happen in various scenarios.
    * Drop this in it's a wrapper of a string.
    */
   struct TestCopyVsAssign
   {
      TestCopyVsAssign()  = default;
      ~TestCopyVsAssign() = default;

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
}
