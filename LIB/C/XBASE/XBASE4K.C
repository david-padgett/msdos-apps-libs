/* File        : XBASE4K.C
   Module      : XBASE
   System      : None
   Description : A method for determining the name of the DBF file currently
                 in use.
   Modified    : 02/15/91 DWP Created.
*/

#include <errno.h>

#include "xbase0.h"

/* Function    : XBASE_Dbf
   Description : Determines the name of the DBF file currently in use.
   Expects     : Nothing.
   Returns     : The name of the DBF file which is in use in the current work
                 area.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
char *XBASE_Dbf(void) {

   XBASE_error_code = EZERO;

   return (((XBASE_work_area *) XBASE_current_work_area)->dbf_file);
}
