#pragma once

#if defined(_MSC_VER)
#   define debug_break() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#   include <csignal>
#   define debug_break() raise(SIGTRAP)
#else
#   define debug_break() ((void)0)
#endif

// Function call is just an expression so we use a comma expression to return only the second part and still invoke the function's side effect.

#ifdef _DEBUG
#   define ensure(cond) ((cond) ? true : (debug_break(), false))
#else
#   define ensure(cond) (cond)
#endif
