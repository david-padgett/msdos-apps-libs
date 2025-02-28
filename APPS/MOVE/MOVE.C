/* File        : MOVE.C
   Module      : MOVE
   System      : MOVE
   Description :
   Modified    : 07/23/91 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <stdio.h>

#include "dir\dir.h"
#include "msdos\msdos.h"
#include "list\list.h"

int pascal DIR_Rename_Directory1(char far *new_name, char far *old_name);

/* Function    : main
   Description : The entry point to the MOVE program.
   Expects     : argv[1] = The file(s) that are to be moved.
                 argv[2] = The destination of the files that are to be moved.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/23/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   int i, result;

   printf("\nMOVE V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc < 3) {
      printf("\n   Purpose : Moves or renames files and/or directories.\n");
      printf("\n   Usage   : MOVE {{[(- | /)<Switch>]} <SourcePathSpec> {<DestinationPathSpec>}}\n");
      printf("\n   Switches\n\n%6sO = Overwrite existing files\n", "");
      result = EZERO;
   }
   else {

      for (i = 1; i < argc; i += 2) {
         if (argv[i] != NULL && argv[i + 1] != NULL) {
            MOVE_Main(argv[i + 1], argv[i]);
         }
      }
   }

   return (result);
}