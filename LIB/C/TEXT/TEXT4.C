/* File        : TEXT4.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Clear_Text_Window
   Description : A method for clearing a text window.
   Inputs      : Nothing.
   Updates     : Text = The TEXT record whose window or screen is to be cleared.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Clear_Text_Window(TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Clear_Text_Window == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Clear_Text_Window(text_descriptor->Window);

   }

   return (result);

}
