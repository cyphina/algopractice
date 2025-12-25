#include <print>
#include <string>

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

   std::println("{}", FromChar1);
   std::println("{}", FromChar2);
   std::println("{}", LongString);
}

int main()
{
   TestStringLiterals();
   TestStringConstructors();
}
