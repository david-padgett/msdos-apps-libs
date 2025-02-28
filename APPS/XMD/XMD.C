/* File        : XMD.C
   Module      : XMD
   System      : XMD
   Description : This program is an enhanced version of the DOS command MD (aka MKDIR).
   Modified    : 05/02/91 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <stdio.h>

#include "dir\dir.h"

/* Function    : main
   Description : This main entry point to the XMD program.  XMD is an enhanced version of the DOS MD (or MKDIR) command.
   Expects     : argv[1] = The directory to create.  This is an optional parameter.
   Returns     : A value of zero if XMD successfully created the specified directory, a non-zero value otherwise.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   int i, result;

   printf("\nXMD V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc == 1) {
      printf("\n   Purpose : Creates multiple directories and sub-directories.\n\n");
      printf("   Usage   : XMD {[Directory]}\n\n");
      printf("   Note\n\n%6sXMD will function properly even if the parent directory(s) of the\n%6snew directory do not exist.\n\n   Example\n\n%6sXMD \\utilities\\xcmds\n", "", "", "");
   }
   else {

      /* Loop until all of the directories specified on the command-line have been created. */

      for (i = 1; argv[i] != NULL; i++) {

         /* If an error occurs while creating the directory, display an error message and exit. */

	 if ((result = DIR_Create_Directory(argv[i])) != EZERO) {
            printf("\nXMD ERROR : Unable to create %s.\n", argv[i]);
            break;
         }
      }
   }

   return (result);
}
