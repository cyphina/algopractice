#include <print>
#include <ranges>
#include <string>
#include "core/StringUtils.h"

void TestStringLiterals()
{
   std::println(R"-(Embedded )" characters)-");
   // Single line
   std::println("Yo"
                "Mom"
                "Sucks!!!");
}

void TestStringConstructors()
{
   const char* TestChars{"Wee!"};

   // Print to initializer list stuff so use ()

   std::string FromChar1("Hello World!");
   std::string FromChar2(TestChars);
   std::string LongString(1000u, 'w');

   std::println("From Char {}", FromChar1);
   std::println("From C String {}", FromChar2);
   std::println("Init Count {}", LongString);
}

void TestSplitString()
{
   std::string Test{"W E E E E !"};
   auto        SplittedTest{StringUtils::Split(Test, ' ')};
   std::println("Split C++20 - {}", SplittedTest);
}

void TestTrimString()
{
   std::string Test{"   WEEEE!  "};
   auto        TrimTest{StringUtils::Trim(Test)};
   std::println("Trim C++20 - {} {}", Test, TrimTest);
}

int main()
{
   TestStringLiterals();
   TestStringConstructors();
   TestSplitString();
   TestTrimString();
}
