/* File        : XBASE4R.C
   Module      : XBASE
   System      : None
   Description : A method for calculating exponents.
   Modified    : 02/19/91 DWP Created.
*/

#include <math.h>

#include "xbase0.h"

/* Function    : XBASE_Exp
   Description : A method for calculating the e to the specified power (e^x).
   Expects     : value = The value whose exponent is desired.
   Returns     : The value of e^value, or e raised to the power of value.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
double XBASE_Exp(double value) {

   return (exp(value));
}
