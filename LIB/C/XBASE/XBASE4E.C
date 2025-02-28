/* File        : XBASE4E.C
   Module      : XBASE
   System      : None
   Description : A method for converting a number to an ASCII code.
   Modified    : 02/14/91 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Chr
   Description : A method for converting a number in the range [0..255] to and ASCII code.
   Expects     : value = The number to convert.
   Returns     : The ASCII code for the specified number.
   Modified    : 02/14/91 DWP Initial coding.
   Notes       : 1) This function is for compatibility only.  It performs no real service.
*/
char XBASE_Chr(unsigned int value) {

   return ((char) value);
}
