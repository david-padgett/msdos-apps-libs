/*
/* File        : COMPUNCP.C
   Module      : COMPUNCP
   System      : COMPUNCP
   Description : An example file compression utility that uses the LZW
                 module.
   Modified    : 09/28/90 DWP Created.
*/

#include <alloc.h>
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdlib.h>

#include "lzw.h"

/* Function    : main
   Description : The main entry point for COMPUNCP.
   Expects     : argc
                 argv
   Returns     : The result of the operation (0 - no errors).
   Modified    : 09/28/90 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   FILE   *fp;
   long   compressed_file_size, original_file_size;
   int    result;

   if (argc >= 4) {

      clrscr();

      switch (toupper(argv[1][0])) {

         case 'A' : result = lzw_compress_file(argv[2], argv[3]);
                    break;

         case 'S' : _lzw_buffer_size = atoi(argv[4]);
                    result = lzw_compress_file(argv[2], argv[3]);
                    break;

                    /* Compress with optimization. */

         case 'O' : if ((fp = fopen(argv[2], "rb")) != NULL) {
                       original_file_size = filelength(fileno(fp));
                       printf("File Name : %-32.32s\nFile Size : %10ld\n\n", argv[2], original_file_size);
                       fclose(fp);
                       for (_lzw_buffer_size = 2048; _lzw_buffer_size != (size_t) 65536L; _lzw_buffer_size += 2048) {
                          if ((result = lzw_compress_file(argv[2], argv[3])) != 0) {
                             break;
                          }
                          compressed_file_size = -1L;
                          if ((fp = fopen(argv[3], "rb")) != NULL) {
                             compressed_file_size = filelength(fileno(fp));
                             fclose(fp);
                          }
                          printf("Buffer Size : %5u     File Size : %10ld     %% Reduction : %03.02f\n", _lzw_buffer_size, compressed_file_size, ((float) compressed_file_size) * 100 / original_file_size);
                       }
                    }
                    break;

                    /* Decompress. */

         case 'E' :
         case 'X' : result = lzw_uncompress_file(argv[2], argv[3]);
                    break;

                    /* Invalid command. */

         default  : result = -1;
      }
   }
   else {
      result = EZERO;
   }

   if (result) {
      printf("\nError %d occurred.\n", result);
   }

   return (result);
}

*/