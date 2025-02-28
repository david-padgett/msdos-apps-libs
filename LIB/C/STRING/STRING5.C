/* File        : STRING5.C
   Module      : STRING
   System      : None
   Description : A method for determining the position of a character in a string.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include "string.h"

/* Function    : STRING_CharPos
   Description : Determines the position of the specified character in the specified string.  If the parameter source is non-NULL,
                 the search starts at the beginning of the string, if the parameter source is NULL, then the search continues with
                 the string that was last specified (ie: the position of the next character is determined).
   Inputs      : String = The string to search.
                 Ch     = The character to search for.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value equal to zero if the character was not found in the string, otherwise, the position in the string of the
                 character.
   Modified    : 07/10/90 DWP Initial coding.
   Notes       :
*/

size_t STRING_CharPos(const char * String, char Ch) {

   static const char * str = NULL;
   static size_t       i = 0;
   size_t              result;

   /* If String is NULL then use the string that was last specified. */

   if (String != NULL) {

      str = String;
      i = 0;

   }

   /* Loop while not end of string. */

   for (result = 0; str[i] != '\0'; i++) {

      /* If the character is found, exit the loop. */

      if (str[i] == Ch) {

         result = ++i;
         break;

      }

   }

   return (result);

}
