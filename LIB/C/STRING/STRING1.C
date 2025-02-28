/* File        : STRING1.C
   Module      : STRING
   System      : None
   Description : A method for removing white space from a string.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <ctype.h>

#include "string.h"

/* Function    : STRING_LTrim
   Description : Removes the leading white space from the specified string.
   Inputs      : Nothing.
   Updates     : String = The string to remove the leading white space from.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 03/12/90 DWP Initial Coding.
                 06/25/90 DWP Enhanced.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_LTrim(char * String) {

   size_t i, j;

   /* Loop until the first non-white space character has been found. */

   for (i = 0; isspace(String[i]); i++) {
   }

   if (String[i] != '\0' && i > 0) {

      j = 0;

      do {

         String[j++] = String[i];

      } while (String[i++] != '\0');

   }

   return (String);

}
