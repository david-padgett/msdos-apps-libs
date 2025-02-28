/* File        : TEXT4C.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Set_Text_Color
   Description : A method for setting the text color attribute.
   Inputs      : Color  = The color to display the text in.
   Updates     : Text   = The TEXT record to initialize.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Set_Text_Color(CARDINAL_16 Color, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Set_Text_Color == NULL) {

      result = TEXT_PARAM;

   }
   else {

      text_descriptor->Color = Color;
      result = text_descriptor->Set_Text_Color(text_descriptor->Window, Color);

   }

   return (result);

}
