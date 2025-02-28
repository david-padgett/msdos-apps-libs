/* File        : TEXT2.C
   Module      : TEXT
   System      : None
   Description : A method for altering the value of the window field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Set_Text_Window
   Description : A method for altering the value fo the window field in the specified TEXT record.
   Inputs      : Window = The new value of the window field.
   Updates     : Text   = The TEXT record to initialize.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Set_Text_Window(void * Window, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || Window == NULL) {

      result = TEXT_PARAM;

   }
   else {

      text_descriptor->Window = Window;
      result = TEXT_NOERR;

   }

   return (result);

}
