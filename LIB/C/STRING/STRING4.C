/* File        : STRING4.C
   Module      : STRING
   System      : None
   Description : A method for comparing strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include "string.h"

/* Function    : STRING_Compare
   Description : Compares two strings for at most length characters or until a NULL character is encountered in either one of the
                 strings.
   Inputs      : String_1 = Source string 1.
                 String_2 = Source string 2.
                 Length   = The maximum number of characters to compare.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value less than zero if String_1 is less than String_2, a value equal to zero if String_1 is equal to String_2,
                 or a value greater than zero if String_1 is greater than String_2.
   Modified    : 06/05/90 DWP Initial coding.
   Notes       : 1) The return value also indicates the position in which the two strings diverged.
*/

long STRING_Compare(char * String_1, char * String_2, int Length) {

   size_t i;
   long   result;

   /* Loop while not end of string (for both String_1 and String_2). */

   for (i = 0, result = 0L; i < Length; i++) {

      /* Check to see if String_1 is less than String_2. */

      if (String_1[i] < String_2[i]) {

         result = (long) -(i + 1L);
         break;

      }

      /* Check to see if String_1 is greater than String_2. */

      if (String_1[i] > String_2[i]) {

         result = (long) (i + 1L);
         break;

      }

      /* Exit the loop if the end of one of the two source strings has been encountered. */

      if (String_1[i] == '\0' || String_2[i] == '\0') {

         break;

      }

   }

   return (result);

}
