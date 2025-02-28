/* File        : STRING6A.C
   Module      : STRING
   System      : None
   Description : A method for inserting a character into an ASCIIZ string.
   Modified    : 07/18/91 DWP Created.
   Notes       :
*/

#include "string.h"

/* Function    : STRING_Insert_Character
   Description : Inserts the specified character into the specified string at the specified position.
   Inputs      : Position  = The position in the string in which to insert the character.
                 Character = The character that is to be inserted into the string.
   Updates     : String    = The string to modify.
   Outputs     : Nothing.
   Returns     : A reference to the parameter 'String'.
   Modified    : 07/18/91 DWP Initial coding.
   Notes       :
*/

char * STRING_Insert_Character(size_t Position, char Character, char * String) {

   size_t i;
   char   swap_buffer;

   for (i = 0; String[i] != '\0'; i++) {

      if (i >= Position) {

         swap_buffer = String[i];
         String[i] = Character;
         Character = swap_buffer;

      }

   }

   String[i] = Character;
   String[i + 1] = '\0';

   return (String);

}