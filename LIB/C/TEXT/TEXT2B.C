/* File        : TEXT4A.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Set_Cursor_Row
   Description : A method for positioning the cursor.
   Inputs      : Row  = The row to display the text on.
   Updates     : Text = The TEXT record whose cursor position is to be modified.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Set_Cursor_Row(CARDINAL_16 Row, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Set_Cursor_Row == NULL) {

      result = TEXT_PARAM;

   }
   else {

      text_descriptor->Row = Row;
      result = text_descriptor->Set_Cursor_Row(text_descriptor->Window, Row);

   }

   return (result);

}
