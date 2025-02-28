/* File        : STRING1C.C
   Module      : STRING
   System      : None
   Description : A method for removing characters from strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include "string.h"

/* Function    : STRING_STrim
   Description : Replaces sequences of the specified character with 1 of the specified character in the specified string.
   Inputs      : Ch     = The character whose repetitive sequence is to be shortened.
   Updates     : String = The string to process.
   Outputs     : Nothing.
   Returns     : A reference to the parameter String.
   Modified    : 05/15/90 DWP Initial Coding.
                 07/09/90 DWP Enhanced, added parameter Ch.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_STrim(char Ch, char * String) {

   size_t i, j;

   /* Loop while not end of string. */

   for (i = j = 0; String[i] != '\0';) {

      /* Search for the character sequence. */

      if (String[i] == Ch) {

         while (String[i + 1] == Ch) {

            i++;

         }

      }

      /* Move the remaining string, if necessary. */

      if (i == j) {

         while (String[++i] != Ch && String[i] != '\0') {
         }

         j = i;

      }
      else {

         do {

            if ((String[j++] = String[i]) == '\0') {

               break;

            }

         } while (String[++i] != Ch);

      }

   }

   return (String);

}
