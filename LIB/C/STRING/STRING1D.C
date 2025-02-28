/* File        : STRING1D.C
   Module      : STRING
   System      : None
   Description : A method for removing characters from strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <ctype.h>

#include "string.h"
#include "Standard\standard.h"

/* Function    : STRING_Trim
   Description : Removes all of the specified character from the specified string.
   Inputs      : Ch     = The character to remove from string, any character in the set [0..255],
                             STRING_TRIM_ALNUM  - removes all alphanumeric characters,
                             STRING_TRIM_ALPHA  - removes all letters,
                             STRING_TRIM_DIGIT  - removes all digits,
                             STRING_TRIM_CNTRL  - removes all control characters,
                             STRING_TRIM_ASCII  - removes all ASCII characters,
                             STRING_TRIM_PRINT  - removes all printable characters,
                             STRING_TRIM_GRAPH  - same as STRING_TRIM_PRINT except spaces are not removed,
                             STRING_TRIM_LOWER  - removes all lowercase letters,
                             STRING_TRIM_UPPER  - removes all uppercase letters,
                             STRING_TRIM_PUNCT  - removes all punctuation,
                             STRING_TRIM_SPACE  - removes all white space,
			     STRING_TRIM_XDIGIT - removes all hexadecimal digits.
   Updates     : String = The string to remove characters from.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 06/21/90 DWP Inital coding.
                 07/09/90 DWP Enhanced.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_Trim(int Ch, char * String) {

   size_t  i, j;
   BOOLEAN remove_flag;

   /* Loop while not end of string. */

   for (i = j = 0, remove_flag = FALSE; String[i] != '\0';) {

      /* Determine if character is to be removed. */

      switch (Ch) {

         case STRING_TRIM_ALNUM :

            if (isalnum(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_ALPHA :

            if (isalpha(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_DIGIT  :

            if (isdigit(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_CNTRL :

            if (iscntrl(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_ASCII :

            if (isascii(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_PRINT :

            if (isprint(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_GRAPH :

            if (isgraph(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_LOWER :

            if (islower(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_UPPER :

            if (isupper(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_PUNCT :

            if (ispunct(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_SPACE :

            if (isspace(String[i])) {

               remove_flag = TRUE;

            }

            break;

         case STRING_TRIM_XDIGIT :

            if (isxdigit(String[i])) {

               remove_flag = TRUE;

            }

            break;

         default :

            if (String[i] == (char) Ch) {

               remove_flag = TRUE;

            }

      }

      /* Shift remaining string to the left, if necessary. */

      if (remove_flag) {

         String[i] = String[++j];
         remove_flag = FALSE;

      }
      else {

         if (++i != ++j) {

            String[i] = String[j];

         }

      }

   }

   return (String);

}
