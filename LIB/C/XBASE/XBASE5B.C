/* File        : XBASE4B.C
   Module      : XBASE
   System      : None
   Description : A method for determining record sizes.
   Modified    : 02/08/91 DWP Created.
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Recsize
   Description : A method for determining the size of the records in the
                 DBF file which is open in the current work area.
   Expects     : Nothing.
   Returns     : The size of a record in the DBF file open in the current
                 work area.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       : 1) If no DBF file is open in the current work area, or if
                    an error occurred while trying to access the DBF file
                    information, a value of zero is returned.
*/
CARDINAL_16 XBASE_Recsize(void) {
   XBASE_work_area *work_area;
   CARDINAL_16       result = 0;

   XBASE_error_code = EZERO;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area != NULL) {
      if (work_area->in_use_flag) {
         result = work_area->header_record.total_bytes_in_record;
      }
   }
   else {
      XBASE_error_code = EINVDAT;
   }

   return (result);
}
