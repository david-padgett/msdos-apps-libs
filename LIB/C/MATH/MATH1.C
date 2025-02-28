/* File        : MATH1.C
   Module      : MATH
   System      : None
   Description : A method for calculating integer powers.
   Modified    : 08/01/90 DWP Created from "MATH.C".
   Notes       :
*/

#include "math.h"

/* Function    : MATH_Integer_Power
   Description : Determines the result of x to the y (x^y).
   Inputs      : X = The base integer.
		 Y = The exponent integer.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of X^Y.
   Modified    : 07/31/90 DWP Initial coding.
   Notes       :
*/

long MATH_Integer_Power(long X, long Y) {

   long result;

   for (result = 1; Y != 0; Y--) {

      result *= X;

   }

   return (result);

}
