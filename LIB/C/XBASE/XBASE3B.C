/* File        : XBASE3B.C
   Module      : XBASE
   System      : None
   Description : A method for re-positioning a DBF file pointer.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "xbase0.h"

/* Procedure   : XBASE_Skip
   Description : Positions the file pointer to the specified location relative to the current position.
   Expects     : offset = The new relative position to move to.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Skip(INTEGER_32 offset) {
   XBASE_work_area *work_area;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area == NULL) {
      XBASE_error_code = EACCES;
   }
   else {
      if (work_area->in_use_flag) {
         _XBASE_Load_Record(work_area->current_record + offset);
      }
   }

   return (XBASE_error_code);
}
