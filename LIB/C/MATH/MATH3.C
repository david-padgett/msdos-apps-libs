/* File        : MATH3.C
   Module      : MATH
   System      : None
   Description : A method for calculating the modulus of two integer numbers.
   Modified    : 02/19/91 DWP Created.
   Notes       :
*/

#include "math.h"

/* Function    : MATH_Modulus
   Description : Determines the true modulus of the specified numbers.
   Inputs      : Numerator   = The numerator of the dividing expression.
		 Denominator = The denominator of the dividing expression.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The result of Numerator modulus Denominator.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/

long MATH_Modulus(long Numerator, long Denominator) {

   return (Numerator - (Denominator * (Numerator / Denominator)));

}