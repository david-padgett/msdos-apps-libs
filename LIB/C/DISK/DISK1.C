/* File        : DISK1.C
   Module      : DISK
   System      : None
   Description : A method for determining the amount of free space on a disk.
   Modified    : 10/05/90 DWP Initial coding.
   Notes       :
*/

#include <dos.h>

#include "Standard\standard.h"

#include "disk.h"

/* Function    : DISK_Free_Space
   Description : Retrieves the amount of disk space available on the specified disk drive.
   Expects     : drive = The drive to query, (0 = Drive A, 1 = Drive B, etc...).
   Returns     : TRUE if the operation was successful, FALSE otherwise.
   Modified    : 10/05/90 DWP Initial coding.
   Notes       : 1) The parameter drive is equivalent to the return value of getdisk().
*/
BOOLEAN DISK_Free_Space(unsigned char drive, unsigned long *free_space) {
   struct dfree fat_info;
   int          result;

   getdfree(drive + 1, &fat_info);

   if (fat_info.df_sclus != 0xffff) {
      *free_space = ((long) fat_info.df_avail) * ((long) fat_info.df_bsec) * ((long) fat_info.df_sclus);
      result = TRUE;
   }
   else {
      result = FALSE;
   }

   return (result);
}
