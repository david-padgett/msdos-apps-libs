/* File        : XBASE4C.C
   Module      : XBASE
   System      : None
   Description : A method for querying the beginning of file flag.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Bof
   Description : A method for querying the beginning of file flag of the DBF file in the current work area.
   Expects     : Nothing.
   Returns     : The value of the beginning of file flag for the DBF file in the current work area.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       : 1) If no DBF file is open in the current work area, or if an error occurred while trying to access the DBF file
                    information record, a value of FALSE is returned.
*/
int XBASE_Bof(void) {
   XBASE_work_area *work_area;
   BOOLEAN         result = FALSE;

   XBASE_error_code = EZERO;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area == NULL) {
      XBASE_error_code = EINVDAT;
   }
   else {
      if (work_area->in_use_flag) {
         result = work_area->beginning_of_file_flag;
      }
   }

   return (result);
}
