/* File        : XBASE4A.C
   Module      : XBASE
   System      : None
   Description : A method for computing the ASCII value of a character.
   Modified    : 02/14/91 DWP Created.
   Notes       :
*/

#include "xbase0.h"

/* Function    : XBASE_Asc
   Description : Computes the ASCII value of the left-most character in the specified string.
   Expects     : string = A pointer to the character whose ASCII value is desired.
   Returns     : The ASCII value of the left-most character in string.
   Modified    : 02/14/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_Asc(char *string) {

   return ((unsigned int) string[0]);
}
