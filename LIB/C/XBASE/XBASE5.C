/* File        : XBASE4.C
   Module      : XBASE
   System      : None
   Description : A method for determining the total number of records in a
                 DBF file.
   Modified    : 02/08/91 DWP Created.
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Reccount
   Description : Returns the number of records present in the DBF file which
                 is currently in use.
   Expects     : Nothing.
   Returns     : The number of records in the current DBF file.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       : 1) If no DBF file is open in the current work area, a value
                    of zero is returned.
*/
CARDINAL_32 XBASE_Reccount(void) {
   XBASE_work_area *work_area;
   CARDINAL_32     result = 0L;

   XBASE_error_code = EZERO;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area != NULL) {
      if (work_area->in_use_flag) {
         result = work_area->header_record.total_records;
      }
   }
   else {
      XBASE_error_code = EINVDAT;
   }

   return (result);
}
