#pragma once

namespace MathUtil
{
   // In C++ and most languages % is the remainder operator, not the true matheamtical modulus.
   int Wrap(int dividend, int modulus);
}
