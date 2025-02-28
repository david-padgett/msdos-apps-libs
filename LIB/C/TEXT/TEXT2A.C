/* File        : TEXT4.C
   Module      : TEXT
   System      : None
   Description : A method for manipulating text.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Set_Cursor_Position
   Description : A method for positioning the cursor.
   Inputs      : Row    = The row to display the text on.
                 Column = The column to display the text on.
   Updates     : Text   = The TEXT record whose cursor position is to be modified.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Set_Cursor_Position(CARDINAL_16 Row, CARDINAL_16 Column, TEXT Text) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Set_Cursor_Position == NULL) {

      result = TEXT_PARAM;

   }
   else {

      text_descriptor->Row = Row;
      text_descriptor->Column = Column;
      result = text_descriptor->Set_Cursor_Position(text_descriptor->Window, Row, Column);

   }

   return (result);

}
