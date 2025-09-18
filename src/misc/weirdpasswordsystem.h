#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace WeirdPasswordSystem
{
   bool AddPassword(std::unordered_map<std::string, int>& PasswordsIndex, std::unordered_set<std::string>& AddedPasswords, std::string_view
                    Password);

   int QueryMatchingPasswords(const std::unordered_map<std::string, int>& PasswordsIndex, const std::string& PasswordToMatch);
}
