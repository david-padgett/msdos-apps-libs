/* File        : XBASE4M.C
   Module      : XBASE
   System      : None
   Description : A method for determining the amount of free disk space on
                 the current disk drive.
   Modified    : 02/15/91 DWP Created.
*/

#include <errno.h>

#include "disk\disk.h"

#include "xbase0.h"

/* Function    : XBASE_Diskspace
   Description : Determines the amount of disk space on the current (default)
                 disk drive.
   Expects     : Nothing.
   Returns     : The number of bytes available on the default disk drive.
   Modified    : 02/15/91 DWP Initial coding.
   Notes       :
*/
unsigned long XBASE_Diskspace(void) {
   unsigned long free_space;

   XBASE_error_code = EZERO;

   if (!DISK_Free_Space(XBASE_default_drive - 'A', &free_space)) {
      XBASE_error_code = EACCES;
   }

   return (free_space);
}
