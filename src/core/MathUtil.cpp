#include "MathUtil.h"

int MathUtil::Wrap(int dividend, int modulus)
{
   // The final mod is to handle if we started out positive.
   // The inner bit is to handle negative stuff >_<
   return ((dividend % modulus) + modulus) % modulus;
}

bool MathUtil::NearlyEqualAbs(double A, double B, double Epsilon)
{
   return std::fabs(A - B) <= Epsilon;
}
