/* File        : CONVERT1.C
   Module      : CONVERT
   System      : None
   Description : Converts base 10 numbers to other bases.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

#include "Math\math.h"

#include "convert.h"

/* Function    : CONVERT_Base
   Description : Converts the specified base 10 number to a new base.
   Inputs      : Base_10_Value   = The base 10 representation of the value to convert.
		 Conversion_Base = The base to convert to.
   Updates     : Nothing.
   Outputs     : Value           = The destination of the converted value.
   Returns     : A reference to the parameter 'Value'.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

char * CONVERT_Base(CARDINAL_32 Base_10_Value, CARDINAL_16 Conversion_Base, char * Value) {

   CARDINAL_32 power, quotient;
   int         i, offset;

   /* Determine which power of the new base to start at. */

   for (i = 0; Base_10_Value >= MATH_Integer_Power(Conversion_Base, i + 1); i++) {
   }

   /* Loop until the entire number has been converted to the new base. */

   for (offset = 0; i >= 0; offset++) {

      power = MATH_Integer_Power(Conversion_Base, i--);
      quotient = Base_10_Value / power;
      Value[offset] = ((quotient < 10) ? '0' : 'A' - 10) + quotient;
      Base_10_Value %= power;

   }

   /* Make sure the new value is an ASCIIZ string. */

   Value[offset] = '\0';

   return (Value);

}
