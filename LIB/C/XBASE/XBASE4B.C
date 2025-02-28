/* File        : XBASE4B.C
   Module      : XBASE
   System      : None
   Description : A method for finding the position of one string which is contained in another string.
   Modified    : 02/14/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "xbase0.h"

/* Function    : XBASE_At
   Description : Determines if string_1 is in string_2.
   Expects     : string_1 = The sub-string to search for.
		 string_2 = The string to search.
   Returns     : If string_1 is in string_2, the starting position of string_1 within string_2, otherwise a value of zero is
		 returned.
   Modified    : 02/14/91 DWP Initial coding.
   Notes       :
*/
unsigned int XBASE_At(char *string_1, char *string_2) {

   return ((strstr(string_2, string_1) - string_2) + 1);
}
