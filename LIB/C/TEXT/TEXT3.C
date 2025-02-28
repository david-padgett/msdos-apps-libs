/* File        : TEXT3.C
   Module      : TEXT
   System      : None
   Description : A method for retrieving the window field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Retrieve_Text_Window
   Description : A method for retrieving the window field in the specified TEXT record.
   Inputs      : Text   = The TEXT record to query.
   Updates     : Nothing.
   Outputs     : Window = The current text window descriptor.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Retrieve_Text_Window(TEXT Text, void ** Window) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL) {

      result = TEXT_PARAM;

   }
   else {

      *(Window) = text_descriptor->Window;
      result = TEXT_NOERR;

   }

   return (result);

}
