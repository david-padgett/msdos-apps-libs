/* File        : DIR2A.C
   Module      : DIRECTORY
   System      : None
   Description : A method for locating files on a disk.
   Modified    : 02/27/91 DWP Created.
   Notes       :
*/

#include <dir.h>

#include "dir.h"

/* Function    : DIR_FindNext
   Description : Continues the directory search initiated by DIR_findfirst().
   Inputs      : Path      = The file path and specification of the file to search for.  This may include drive, path, and file
                             name information as well as wild card characters ('*' and '?').
                 Attribute = The attribute that any prospective files must have.  Any files returned by this function must exactly
                             match this attribute.
   Updates     : Nothing.
   Outputs     : FFBLK     = The buffer for the disk transfers (DTA).
   Returns     : TRUE if a file was found, FALSE otherwise.
   Modified    : 02/27/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN DIR_FindNext(char * Path, int Attribute, struct ffblk * FFBLK) {

   struct ffblk * old_FFBLK;
   BOOLEAN        result = FALSE;

   /* Save registers. */

   asm {

      push  es
      push  ds
      push  dx
      push  cx
      push  bx

   }

   /* Save current DTA. */

   asm {

      mov   ah, 2fh
      int   21h
      mov   old_FFBLK + 2, es
      mov   old_FFBLK, bx

   }

   /* Install the new DTA. */

   asm {

      mov   ax, FFBLK + 2
      mov   ds, ax
      mov   dx, FFBLK
      mov   ah, 1ah
      int   21h

   }

   while (TRUE) {

      /* Find the next file. */

      asm {

         mov   ax, Path + 2
         mov   ds, ax
         mov   dx, Path
         mov   cx, Attribute
         mov   ah, 4fh
         int   21h

         jc    label_0

      }

      /* If the attribute of the found file and the specified attribute are identical, exit. */

      if (FFBLK->ff_attrib == Attribute) {

         result = TRUE;
         break;

      }

   }

   label_0:;

   /* Restore original DTA. */

   asm {

      mov   ax, old_FFBLK + 2
      mov   ds, ax
      mov   dx, old_FFBLK
      mov   ah, 1ah
      int   21h

   }

   /* Restore registers. */

   asm {

      pop   bx
      pop   cx
      pop   dx
      pop   ds
      pop   es

   }

   return (result);

}