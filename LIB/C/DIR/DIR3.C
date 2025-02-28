/* File        : DIR3.C
   Module      : DIR
   System      : None
   Description : A method for creating a directory.
   Modified    : 05/02/91 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <io.h>
#include <stdio.h>

#include "dir.h"

/* Function    : DIR_Create_Directory
   Description : Creates the specified directory.  If the specified directory is a directory path that does not yet exist, the
                 directory path is created as well.
   Inputs      : Directory = The directory specification to create.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/

int DIR_Create_Directory(char * Directory) {

   size_t i;
   char   separator_character;
   int    result = EZERO;

   /* Loop until an error occurs or until there are no more characters in the directory specification to process. */

   for (i = 0; result == EZERO; i++) {

      if (i > 0 && Directory[i - 1] != ':' && (Directory[i] == '\\' || Directory[i] == '\0')) {

         separator_character = Directory[i];
         Directory[i] = '\0';

         if (access(Directory, 0) != 0) {

            result = (mkdir(Directory) == 0) ? EZERO : errno;

         }

         Directory[i] = separator_character;

         /* Exit if there are no more characters to process in the directory specification. */

         if (Directory[i] == '\0') {

            break;

         }

      }

   }

   return (result);

}
