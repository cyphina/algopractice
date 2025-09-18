#include "weirdpasswordsystem.h"

bool WeirdPasswordSystem::AddPassword(std::unordered_map<std::string, int>& PasswordsIndex, std::unordered_set<std::string>& AddedPasswords,
                                      std::string_view Password)
{
   std::string StoredPassword{Password};
   if(AddedPasswords.contains(StoredPassword))
   {
      return false;
   }

   AddedPasswords.emplace(std::move(StoredPassword));

   std::unordered_set<std::string_view> NewlyAddedSubstrings;
   for(int i = 0; i < Password.size(); ++i)
   {
      for(int j = 0; j < Password.size(); ++j)
      {
         const auto NewSubstring{std::string(Password.substr(i, j + 1))};
         if(!NewlyAddedSubstrings.contains(NewSubstring))
         {
            NewlyAddedSubstrings.emplace(NewSubstring);
            ++PasswordsIndex[std::string(std::move(NewSubstring))];
         }
      }
   }

   return true;
}

int WeirdPasswordSystem::QueryMatchingPasswords(const std::unordered_map<std::string, int>& PasswordsIndex, const std::string& PasswordToMatch)
{
   if(PasswordsIndex.contains(PasswordToMatch))
   {
      return PasswordsIndex.find(PasswordToMatch)->second;
   }

   return 0;
}
