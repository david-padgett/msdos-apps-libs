/* File        : XBASE4S.C
   Module      : XBASE
   System      : None
   Description : A method for retrieving the name of a field in a database.
   Modified    : 02/19/91 DWP Created.
*/

#include <math.h>
#include <string.h>

#include "xbase0.h"

/* Function    : XBASE_Field
   Description : A method for retrieving the name of the specified field
                 in the currently selected database.
   Expects     : field = The field whose name is desired.
   Returns     : The name of the specified field.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
const char *XBASE_Field(int field) {

   if (field > 0 && field <= XBASE_current_work_area->number_of_fields) {
      strncpy(XBASE_field_string, XBASE_current_work_area->field_list[field - 1].field_name, sizeof(XBASE_field_string) - 1);
   }
   else {
      XBASE_field_string[0] = '\0';
   }

   return (XBASE_field_string);
}
