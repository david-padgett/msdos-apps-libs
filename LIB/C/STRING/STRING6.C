/* File        : STRING6.C
   Module      : STRING
   System      : None
   Description : A method for removing a character from a ASCIIZ string.
   Modified    : 07/18/91 DWP Created.
   Notes       :
*/

#include "string.h"

/* Function    : STRING_Delete_Character
   Description : Removes the character which is located at the specified position in the specified ASCIIZ string.
   Inputs      : Position = The position of the character that is to be removed from the specified string.
   Updates     : String   = The string to modify.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 07/18/91 DWP Initial coding.
   Notes       :
*/

char * STRING_Delete_Character(size_t Position, char * String) {

   size_t i;

   for (i = 0; String[i] != '\0'; i++) {

      if (i >= Position) {

         String[i] = String[i + 1];

      }

   }

   return (String);

}
