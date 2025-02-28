/* File        : TEXT4B.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Print_String
   Description : A method for printing a string on the screen.
   Inputs      : String = The string to print.
   Updates     : Text   = The TEXT record whose screen is to be updated.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Print_String(char * String, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Print_String == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Print_String(text_descriptor->Window, String);

   }

   return (result);

}
