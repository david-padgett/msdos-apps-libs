/* File        : TEXT3B.C
   Module      : TEXT
   System      : None
   Description : A method for retrieving the color field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Retrieve_Text_Color
   Description : A method for retrieving the color field in the specified TEXT record.
   Inputs      : Text  = The TEXT record to query.
   Updates     : Nothing.
   Outputs     : Color = The current text color.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Retrieve_Text_Color(TEXT Text, CARDINAL_16 * Color) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Get_Text_Color == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Get_Text_Color(text_descriptor->Window, Color);
      text_descriptor->Color = *(Color);

   }

   return (result);

}
