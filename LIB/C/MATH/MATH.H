/* File        : MATH.H
   Module      : MATH
   System      : None
   Description : The header file for the MATH module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _MATH_MODULE
#define _MATH_MODULE

typedef enum _MATH_ROUND_DIRECTION_TYPES {MATH_ROUND_UP, MATH_ROUND_DOWN} MATH_ROUND_DIRECTION_TYPES;

/* Procedures and Functions. */

long   MATH_Integer_Power(long X, long Y);
long   MATH_Integer_Round(MATH_ROUND_DIRECTION_TYPES Direction, int Decimal_Place, long Value);
double MATH_Real_Round(MATH_ROUND_DIRECTION_TYPES Direction, int Decimal_Place, double Value);
long   MATH_Modulus(long Numerator, long Denominator);

#endif
