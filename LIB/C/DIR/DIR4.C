/* File        : DIR4.C
   Module      : DIRECTORY
   System      : None
   Description : A method for determining at what level in a directory tree a file is located.
   Modified    : 05/10/91 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "MSDos\msdos.h"

#include "dir.h"

/* Function    : DIR_Calculate_File_Specification_Level
   Description : Determines at what level in the directory tree the given file specification is located.
   Inputs      : File_Spec = The file specification whose directory tree level is desired.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The level of the file or directory specified by File_Spec in the directory tree to which it belongs.  A value of
                 zero indicates that the root directory was specified, or that the level could not be determined from the given
                 file specification.
   Modified    : 05/20/91 DWP Initial coding.
   Notes       : 1) The return value is equal to the number of backslash '\' characters found in the fully qualified file
                    specification.
                 2) Examples of the return value of this function are as follows:

                    result - File_Spec
                    ------   ---------
                      0      \                    - Root directory.
                      0      C:\                  - Root directory.
                      1      C:\TEST.DAT          - File in root directory.
                      2      C:\DOS\XCOPY.EXE     - File in sub-directory.
                      3      C:\C\BORLANDC\BC.EXE - File in 2nd level
                                                    sub-directory.
*/

CARDINAL_16 DIR_Calculate_File_Specification_Level(char * File_Spec) {

   char        fully_qualified_file_spec[MAXPATH];
   size_t      i;
   CARDINAL_16 result;

   DOS_Qualify_File_Specification(fully_qualified_file_spec, File_Spec);

   /* Loop until the entire fully qualified file specification has been examined. */

   for (i = 0, result = 0; fully_qualified_file_spec[i] != '\0'; i++) {

      /* If a backslash character was found, and if the backslash character is followed by a file specification, then increment
         the current level.  If the backslash character is the last character in the file specification, then exit. */

      if (fully_qualified_file_spec[i] == '\\') {

         if (fully_qualified_file_spec[i + 1] == '\0') {

            break;

         }

         result++;

      }

   }

   return (result);

}
