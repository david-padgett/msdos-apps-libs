/* File        : STRING3.C
   Module      : STRING
   System      : None
   Description : A method for re-formatting strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <string.h>

#include "string.h"

/* Function    : STRING_Delimit
   Description : Adds the specified delimiters at the specified interval starting from the specified direction for the specified
                 string.
   Inputs      : Interval  = The interval, or space, between each delimiter.
                 Direction = The direction to start from, see STRING_DELIMIT_DIRECTION_TYPES.
                 Delimiter = The delimiter to insert into the string.
   Updates     : String    = The string to insert delimiters into.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 07/19/90 DWP Initial coding.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_Delimit(size_t Interval, STRING_DELIMIT_DIRECTION_TYPES Direction, char * Delimiter, char * String) {

   size_t str_length, del_length, new_length;
   size_t i, j, pos;

   str_length = strlen(String);
   del_length = strlen(Delimiter);
   new_length = str_length + (((str_length / Interval) - ((str_length % Interval) ? 0 : 1)) * del_length);

   String[new_length] = '\0';

   j = (Direction == STRING_DELIMIT_LEFT) ? (str_length % Interval) ? Interval - (str_length % Interval) : 0 : 0;

   for (i = str_length, pos = new_length - 1; i != 0; i--, pos--) {

      if (j++ == Interval) {

         j = 1;
         strncpy(String + pos - del_length + 1, Delimiter, del_length);
         pos -= del_length;

      }

      String[pos] = String[i - 1];

   }

   return (String);

}
