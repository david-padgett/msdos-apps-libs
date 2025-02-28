/* File        : MATH2.C
   Module      : MATH
   System      : None
   Description : A method for rounding integers.
   Modified    : 08/01/90 DWP Created from "MATH.C".
   Notes       :
*/

#include "math.h"
#include "Standard\standard.h"

/* Function    : MATH_Integer_Round
   Description : Rounds the specified value in the specified direction to the specified decimal place.
   Inputs      : Direction     = The direction to round, [UP | DOWN].
		 Decimal_Place = The decimal place to round to.
		 Value         = The number to be rounded.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The rounded number.
   Modified    : 07/30/90 DWP Initial coding.
   Notes       :
*/

long MATH_Integer_Round(MATH_ROUND_DIRECTION_TYPES Direction, int Decimal_Place, long Value) {

   long divisor, remainder, power, result = Value;

   if (Decimal_Place > 0) {

      power = MATH_Integer_Power(10L, Decimal_Place);
      divisor = (Value * 10L) / power;
      remainder = divisor % 10L;
      divisor /= 10L;

      result = (divisor + ((Direction == MATH_ROUND_UP) ? ((remainder > 4) ? 1L : 0L) : 0L)) * power;

   }

   return (result);

}
