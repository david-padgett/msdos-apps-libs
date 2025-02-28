/* File        : STRING1B.C
   Module      : STRING
   System      : None
   Description : A method for removing white space from strings.
   Modified    : 08/01/90 DWP Created from "STRING.C".
   Notes       :
*/

#include <ctype.h>

#include "string.h"

/* Function    : STRING_ATrim
   Description : Removes both leading and trailing spaces from the specified string.
   Inputs      : Nothing.
   Updates     : String = The string to remove leading/trailing white space from.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 03/12/90 DWP Initial Coding.
   Notes       : 1) For use with standard C (NULL terminated) strings only.
*/

char * STRING_ATrim(char * String) {

   return (STRING_LTrim(STRING_RTrim(String)));

}
