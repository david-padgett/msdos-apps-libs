/* File        : TEXT3B.C
   Module      : TEXT
   System      : None
   Description : A method for retrieving the column field in an instance of a TEXT record.
   Modified    : 03/04/92 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "text0.h"

/* Function    : TEXT_Retrieve_Cursor_Column
   Description : A method for retrieving the column field in the specified TEXT record.
   Inputs      : Text   = The TEXT record to query.
   Updates     : Nothing.
   Outputs     : Column = The current text column.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/04/92 DWP Initial coding.
   Notes       :
*/

int TEXT_Retrieve_Cursor_Column(TEXT Text, CARDINAL_16 * Column) {

   _TEXT * text_descriptor;
   int     result;

   if ((text_descriptor = Text) == NULL || text_descriptor->Get_Cursor_Column == NULL) {

      result = TEXT_PARAM;

   }
   else {

      result = text_descriptor->Get_Cursor_Column(text_descriptor->Window, Column);
      text_descriptor->Column = *(Column);

   }

   return (result);

}
