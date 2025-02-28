/* File        : XBASE3C.C
   Module      : XBASE
   System      : None
   Description : A method for re-positioning the DBF file pointer.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Goto
   Description : Positions the DBF file pointer to the specified absolute location.
   Expects     : position = The record to go to.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Goto(INTEGER_32 position) {
   XBASE_work_area *work_area;

   LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
   if (work_area == NULL) {
      XBASE_error_code = EACCES;
   }
   else {

      if (work_area->in_use_flag) {

         switch (position) {

            case TOP    : position = 1L;
                          break;

            case BOTTOM : position = work_area->header_record.total_records;
                          break;
         }

         _XBASE_Load_Record(position);
      }
   }

   return (XBASE_error_code);
}
