#pragma once
#include <cmath>

namespace MathUtil
{
   // In C++ and most languages % is the remainder operator, not the true matheamtical modulus.
   int Wrap(int dividend, int modulus);

   // Check to see if absolute difference (distance) is within a fixed tolerance. Can use std::isclose too.
   bool NearlyEqualAbs(double A, double B, double Epsilon = 1e-6)
   {
      return std::fabs(A -) <= Epsilon;
   }
}
