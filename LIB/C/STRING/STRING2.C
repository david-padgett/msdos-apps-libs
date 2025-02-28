/* File        : STRING2.C
   Module      : STRING
   System      : None
   Description : A method for re-formatting strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <string.h>

#include "string.h"

/* Function    : STRING_Center
   Description : Center justifies the specified string in the specified width.
   Inputs      : Size   = The new length of the string being modified.
   Updates     : String = The string to center justify.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 05/29/90 DWP Initial coding.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
                 2) String should be at least Size characters long.
*/

char * STRING_Center(int Size, char * String) {

   size_t i, length, max_pos = Size;

   length = strlen(STRING_ATrim(String));

   /* If the string is longer than the specified size, then do not center the string. */

   if (Size > length) {

      /* Center the string. */

      Size = (Size - length) / 2;
      memmove(String + Size, String, length);

      /* Make sure that the leading characters are all spaces. */

      for (i = 0; i < Size; i++) {

         String[i] = ' ';

      }

      /* Make sure that that trailing characters are all spaces. */

      for (i = Size + length; i < max_pos; i++) {

         String[i] = ' ';

      }

      /* Make sure the string is NULL terminated. */

      String[i] = '\0';

   }

   return (String);

}
