/* File        : TEXT3A.C
   Module      : TEXT
   System      : None
   Description : A method for retrieving the row field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Retrieve_Cursor_Row
   Description : A method for retrieving the row field in the specified TEXT record.
   Inputs      : Text = The TEXT record to query.
   Updates     : Nothing.
   Outputs     : Row  = The current text row.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Retrieve_Cursor_Row(TEXT Text, CARDINAL_16 * Row) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Get_Cursor_Row == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Get_Cursor_Row(text_descriptor->Window, Row);
      text_descriptor->Row = *(Row);

   }

   return (result);

}
