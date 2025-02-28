/* File        : XBASE4L.C
   Module      : XBASE
   System      : None
   Description : A method for determining whether or not a record is deleted.
   Modified    : 02/15/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Deleted
   Description : Determines whether or not the record currently in use is
                 deleted.
   Expects     : Nothing.
   Returns     : TRUE if the record is deleted, FALSE otherwise.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Deleted(void) {

   return ((((XBASE_work_area *) XBASE_current_work_area)->xbase_record[0] == XBASE_DELETED_RECORD) ? TRUE : FALSE);
}
