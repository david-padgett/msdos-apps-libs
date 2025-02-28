/* File        : MATH2A.C
   Module      : MATH
   System      : None
   Description : A method for rounding real numbers.
   Modified    : 08/01/90 DWP Created from "MATH.C".
   Notes       :
*/

#include <math.h>

#include "math.h"
#include "Standard\standard.h"

/* Function    : MATH_Real_Round
   Description : Rounds the specified value in the specified direction to the
		 specified decimal place.
   Inputs      : Direction     = The direction to round, [UP | DOWN].
		 Decimal_Place = The decimal place to round to.
		 Value         = The number to be rounded.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The rounded number.
   Modified    : 07/31/90 DWP Initial coding.
   Notes       :
*/

double MATH_Real_Round(MATH_ROUND_DIRECTION_TYPES Direction, int Decimal_Place, double Value) {

   long   divisor, remainder, power;
   double adjustment, result = Value;

   if (Decimal_Place != 0) {

      power = MATH_Integer_Power(10, abs(Decimal_Place));
      adjustment = (double) power;

      if (Decimal_Place > 0) {

	 divisor = ((long) (Value * 10.0)) / power;

      }
      else {

	 divisor = (long) (Value * 10.0 * power);
	 adjustment = 1 / adjustment;

      }

      remainder = divisor % 10L;
      divisor /= 10L;
      result = (divisor + ((Direction == MATH_ROUND_UP) ? ((remainder > 4) ? 1 : 0) : 0)) * adjustment;

   }

   return (result);

}
