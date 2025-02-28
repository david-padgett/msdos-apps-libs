/* File        : TEXT4A.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Print_Character
   Description : A method for printing text on the screen.
   Inputs      : Character = The character to print.
   Updates     : Text      = The TEXT record whose screen is to be modified.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Print_Character(char Character, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Print_Character == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Print_Character(text_descriptor->Window, Character);

   }

   return (result);

}

