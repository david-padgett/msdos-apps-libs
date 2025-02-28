/* File        : XBASE4P.C
   Module      : XBASE
   System      : None
   Description : A method for querying the end of file flag.
   Modified    : 02/15/91 DWP Created.
*/

#include "xbase0.h"

/* Function    : XBASE_Eof
   Description : A method for querying the end of file flag of the DBF file
                 in the current work area.
   Expects     : Nothing.
   Returns     : The value of the end of file flag for the DBF file in the
                 current work area.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       : 1) If no DBF file is open in the current work area, a value
                    of FALSE is returned.
*/
unsigned int XBASE_Eof(void) {

   return (((XBASE_work_area *) XBASE_current_work_area)->end_of_file_flag);
}
