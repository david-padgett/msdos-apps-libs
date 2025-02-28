/* File        : TEXT3D.C
   Module      : TEXT
   System      : None
   Description : A method for retrieving the font field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Retrieve_Text_Font
   Description : A method for retrieving the font field in the specified TEXT record.
   Inputs      : Text = The TEXT record to query.
   Updates     : Nothing.
   Outputs     : Font = The current text font.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Retrieve_Text_Font(TEXT Text, void ** Font) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL) {

      result = TEXT_PARAM;

   }
   else {

      *(Font) = text_descriptor->Font;
      result = TEXT_NOERR;

   }

   return (result);

}
