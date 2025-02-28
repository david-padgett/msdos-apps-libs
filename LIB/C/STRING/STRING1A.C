/* File        : STRING1A.C
   Module      : STRING
   System      : None
   Description : A method for removing white space from a string.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <ctype.h>

#include "string.h"

/* Function    : STRING_RTrim
   Description : Removes trailing spaces from the specified string.
   Inputs      : Nothing.
   Updates     : String = The string to remove trailing spaces from.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 03/12/90 DWP Initial Coding.
                 06/25/90 DWP Enhanced.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_RTrim(char * String) {

   size_t i, j;

   /* Loop while not end of string. */

   for (i = 0; String[i] != '\0'; i++) {

      /* Search for last sequence of spaces. */

      for (j = i; isspace(String[i]); i++) {
      }

      /* If the character after the last white space character is the NULL character, then adjust the string and exit. */

      if (String[i] == '\0') {

         String[j] = '\0';
         break;

      }

   }

   return (String);

}
