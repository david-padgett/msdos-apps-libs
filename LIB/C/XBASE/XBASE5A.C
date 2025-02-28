/* File        : XBASE4A.C
   Module      : XBASE
   System      : None
   Description : A method for determining the current record number.
   Modified    : 02/08/91 DWP Created.
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Recno
   Description : A method for determining the current record number of the
                 DBF file which is currently in use.
   Expects     : Nothing.
   Returns     : The current record number of the DBF file currently in use.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       : 1) If no DBF file is open in the current work area, or if
                    an error occurred while trying to access the DBF file
                    information, a value of zero is returned.
                 2) If XBASE_Eof() returns TRUE, a value of XBASE_Reccount()
                    + 1 is returned.  This condition occurs either when there
                    are no records in the DBF file or when the file pointer
                    has been moved past the end of the DBF file.
                 3) If XBASE_Bof() returns TRUE, a value of one is returned.
*/
CARDINAL_32 XBASE_Recno(void) {
   XBASE_work_area *work_area;
   CARDINAL_32     result = 0L;

   XBASE_error_code = EZERO;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area != NULL) {
      if (work_area->in_use_flag) {
         result = (work_area->end_of_file_flag) ? work_area->header_record.total_records + 1L : work_area->current_record;
      }
   }
   else {
      XBASE_error_code = EINVDAT;
   }

   return (result);
}
