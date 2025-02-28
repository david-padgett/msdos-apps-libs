/* File        : XBASE4.C
   Module      : XBASE
   System      : None
   Description : A method for computing the absolute value of a real number.
   Modified    : 02/13/91 DWP Created.
   Notes       :
*/

#include "xbase0.h"

/* Function    : XBASE_Abs
   Description : Computes the absolute value of the specified real number.
   Expects     : real_number = The real number whose absolute value is desired.
   Returns     : The absolute value of real_number.
   Modified    : 02/13/91 DWP Initial coding.
   Notes       :
*/
double XBASE_Abs(double real_number) {

   if (real_number < 0.0L) {
      real_number *= -1.0L;
   }

   return (real_number);
}
