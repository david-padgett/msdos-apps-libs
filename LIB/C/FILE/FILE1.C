/* File        : FILE1.C
   Module      : FILE
   System      : None
   Description : A method for copying files.
   Modified    : 08/01/90 DWP Created from "FILE.C".
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "file.h"

/* Function    : FILE_copy
   Description : Copies one file to another.
   Expects     : dest   = The destination file name.
                 source = The source file name.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 03/30/90 DWP Initial Coding.
   Notes       : 1) The file name has the following format:
                     [drive:][\][directory\]name.ext
*/
int FILE_copy(char *dest, char *source) {
   FILE   *dst, *src;
   void   *bufr;
   size_t size, bytes_read;

   if (strcmp(source, dest)) {
      if (((src = fopen(source, "rb")) != NULL) && ((dst = fopen(dest, "wb")) != NULL)) {
         if ((bufr = malloc(size = (size_t) ((coreleft() > 65000L) ? 65000L : coreleft()))) != NULL) {

            while ((bytes_read = fread(bufr, 1, size, src)) > 0) {
               if (fwrite(bufr, bytes_read, 1, dst) == 0) {
                  break;
               }
            }

            free(bufr);
            errno = EZERO;
         }

         fclose(dst);
      }

      if (src != NULL) {
         fclose(src);
      }
   }

   return (errno);
}
