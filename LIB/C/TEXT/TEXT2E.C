/* File        : TEXT2D.C
   Module      : TEXT
   System      : None
   Description : A method for altering the value of the font field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Set_Text_Font
   Description : A method for altering the value of the font field in the specified TEXT record.
   Inputs      : Font = The new value of the font field.
   Updates     : Text = The TEXT record to initialize.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Set_Text_Font(void * Font, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL) {

      result = TEXT_PARAM;

   }
   else {

      text_descriptor->Font = Font;
      result = TEXT_NOERR;

   }

   return (result);

}
