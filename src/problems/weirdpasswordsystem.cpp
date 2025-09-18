#include "misc/weirdpasswordsystem.h"
#include <iostream>
#include <print>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main()
{
   std::unordered_map<std::string, int> Passwords;
   std::unordered_set<std::string>      AddedPasswords;

   Passwords.reserve(100000);

   int         OperationIndex;
   std::string Password;

   while(std::cin)
   {
      std::println("1 (Pass) for Add Password, 2 (Pass) for Query Password (note caps matter)");
      std::cin >> OperationIndex >> Password;

      switch(OperationIndex)
      {
         case 1:
         {
            if(WeirdPasswordSystem::AddPassword(Passwords, AddedPasswords, Password))
            {
               std::println("Added password {}!", Password);
            }
            else
            {
               std::println("Didn't add dupe password {}!", Password);
            }

            break;
         }
         case 2:
         {
            const auto MatchingPasswords{WeirdPasswordSystem::QueryMatchingPasswords(Passwords, Password)};
            std::println("Found {} matching passwords", MatchingPasswords);
            break;
         }
         default:
         {
            std::println("Invalid operation!");
            break;
         }
      }
   }
}
