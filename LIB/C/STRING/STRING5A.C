/* File        : STRING5A.C 
   Module      : STRING
   System      : None
   Description : A method for locating the position, or offset, of one string in another string.
   Modified    : 09/17/92 DWP Created.
   Notes       :
*/

#include <string.h>

#include "string.h"

/* Function    : STRING_StrPos
   Description : Locates the position, or offset, of one string in another string.
   Inputs      : Search_String = The string to search.
                 Sub_String    = The string to search for.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of - 1 if the search string does not contain the sub-string, otherwise, the starting position of the
                 sub-string within the search string.
   Modified    : 09/17/92 DWP Initial coding.
   Notes       :
*/

int STRING_StrPos(char * Search_String, char * Sub_String) {

   int search_string_pos, sub_string_pos, search_string_length, sub_string_length, result;

   result = -1;
   search_string_length = strlen(Search_String);
   sub_string_length = strlen(Sub_String);

   if (search_string_length >= sub_string_length) {

      search_string_length -= (sub_string_length - 1);

      /* Traverse the search string until either the sub-string is located or the end of the search string has been encountered. */

      for (search_string_pos = 0; search_string_pos < search_string_length; search_string_pos++) {

         /* Determine if the sub-string is located starting at the current position within the search string. */

         for (sub_string_pos = 0; Search_String[search_string_pos + sub_string_pos] == Sub_String[sub_string_pos] && sub_string_pos < sub_string_length; sub_string_pos++);

         /* If the sub-string has been found, set the return value and exit. */

         if (sub_string_pos == sub_string_length) {

            result = search_string_pos;
            break;

         }

      }

   }

   return (result);

}