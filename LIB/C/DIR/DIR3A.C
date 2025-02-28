/* File        : DIR3A.C
   Module      : DIR
   System      : None
   Description : A method for deleting sub-directories and their contents.
   Modified    : 05/06/91 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <errno.h>
#include <io.h>
#include <string.h>
#include <sys\stat.h>

#include "dir.h"

/* Function    : DIR_Delete_Directory
   Description : Removes the specified directory, including all of its files and sub-directories.
   Inputs      : Directory = The directory to remove.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/

int DIR_Delete_Directory(char * Directory) {

   struct ffblk ffblk;
   char         search_argument[256], file_name[256];
   int          result = 0;

   strcpy(search_argument, Directory);
   strcat(search_argument, "\\*.*");

   if (findfirst(search_argument, &ffblk, FA_ARCH | FA_DIREC | FA_SYSTEM | FA_HIDDEN | FA_RDONLY) == 0) {

      /* Loop until there are no more files in the specified directory to delete. */

      do {

         /* Skip the '..' and '.' directory files. */

         if (strstr("..", ffblk.ff_name)  == NULL) {

            /* Construct the full file name of the file that being deleted. */

            strcpy(file_name, Directory);
            strcat(file_name, "\\");
            strcat(file_name, ffblk.ff_name);

            /* Alter the characteristic of the file if it a read-only file.  If an error occurs, exit. */

            if ((ffblk.ff_attrib & FA_RDONLY) == FA_RDONLY && chmod(file_name, S_IREAD | S_IWRITE) != 0) {

               result = EACCES;
               break;

            }

            /* Delete the current file if it is not a directory. If an error occurs, exit. */

            if (ffblk.ff_attrib != FA_DIREC && unlink(file_name) != 0) {

               result = ENOFILE;
               break;

            }

            /* If the current file is a directory, delete all of the files and sub-directories in it, then delete the directory.
               If an error occurs, exit. */

            if (ffblk.ff_attrib == FA_DIREC) {

               if ((result = DIR_Delete_Directory(file_name)) != EZERO) {

                  break;

               }

            }

         }

      } while (findnext(&ffblk) == 0);

   }

   /* Delete the specified directory only if no other errors occurred. */

   if (result == EZERO && DIR_Calculate_File_Specification_Level(Directory) > 0) {

      result = (rmdir(Directory) != 0) ? errno : EZERO;

   }

   return (result);

}
