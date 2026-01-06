#include <stack>
#include <string>

// Given a string, check if all brackets ('()', '{}', '[]') are properly matched and nested. Return 1 if valid, otherwise return 0.
// The trick is to handle the various edge cases carefully.
// Check if we have any remaining stuff in the stack aka we had more opening's than closings.
// Handle empty
// Make sure to handle if we have )'s without any ('s.

bool areBracketsProperlyMatched(std::string code_snippet)
{
   std::stack<char> BracketStack;

   for(const auto& Elem : code_snippet)
   {
      if(Elem == '(' || Elem == '{' || Elem == '[')
      {
         BracketStack.push(Elem);
      }
      if(Elem == ')')
      {
         if(BracketStack.empty())
         {
            return false;
         }

         const auto& MatchingBracket = BracketStack.top();
         BracketStack.pop();
         if(MatchingBracket != '(')
         {
            return false;
         }
      }
      else if(Elem == '}')
      {
         if(BracketStack.empty())
         {
            return false;
         }

         const auto& MatchingBracket = BracketStack.top();
         BracketStack.pop();
         if(MatchingBracket != '{')
         {
            return false;
         }
      }
      else if(Elem == ']')
      {
         if(BracketStack.empty())
         {
            return false;
         }

         const auto& MatchingBracket = BracketStack.top();
         BracketStack.pop();
         if(MatchingBracket != '[')
         {
            return false;
         }
      }
   }

   if(BracketStack.empty())
   {
      return true;
   }
   return false;
}

int main()
{
   areBracketsProperlyMatched(")))");
   areBracketsProperlyMatched("((())()");
   areBracketsProperlyMatched("Wee");
}
