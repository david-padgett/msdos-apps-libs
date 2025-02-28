/* File        : DIR2.C
   Module      : DIRECTORY
   System      : None
   Description : A method for locating files on a disk.
   Modified    : 02/27/91 DWP Created.
   Notes       :
*/

#include <dir.h>

#include "dir.h"

/* Function    : DIR_FindFirst
   Description : Finds the first file whose path and name matches the specified path and whose attribute matches the specified
                 attribute.
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

BOOLEAN DIR_FindFirst(char far * Path, int Attribute, struct ffblk far * FFBLK) {

   struct ffblk * current_dta;
   BOOLEAN        result = FALSE;

   /* Save registers. */

   asm {

      push  es
      push  ds
      push  dx
      push  cx
      push  bx

   }

   /* Save old DTA. */

   asm {

      mov   ah, 2fh
      int   21h
      mov   current_dta + 2, es
      mov   current_dta, bx

   }

   /* Establish the new disk transfer address. */

   asm {

      mov   ax, FFBLK + 2
      mov   ds, ax
      mov   dx, FFBLK
      mov   ah, 1ah
      int   21h

   }

   /* Find the first file whose attribute matches exactly the specified attribute using DOS INT 21h subfunction 4Eh. */

   asm {

      mov   ax, Path + 2
      mov   ds, ax
      mov   dx, Path
      mov   cx, Attribute
      mov   ah, 4eh
      int   21h

      jc    near label_0

   }

   while (TRUE) {

      /* If the attribute of the found file and the specified attribute are identical, exit. */

      if (FFBLK->ff_attrib == Attribute) {

	 result = TRUE;
         break;

      }

      /* Find the next file. */

      asm {

         mov   ax, Path + 2
         mov   ds, ax
         mov   dx, Path
         mov   cx, Attribute
         mov   ah, 4fh
         int   21h

         jc    near label_0

      }

   }

   label_0:;

   /* Restore original DTA. */

   asm {

      mov   ax, current_dta + 2
      mov   ds, ax
      mov   dx, current_dta
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