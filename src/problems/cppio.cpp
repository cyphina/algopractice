#include <iostream>
#include <string>

int main()
{
   int         wee;
   std::string pee;
   std::println(std::cout, "Input number and string");
   std::cin >> wee >> pee;
   std::println(std::cout, "{} {}", wee, pee);
}
