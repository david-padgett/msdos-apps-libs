/* File        : LZW3.C
   Module      : LZW
   System      : None
   Description : A method for compressing an entire file.
   Modified    : 09/28/90 DWP Created.
*/

#include <alloc.h>
#include <errno.h>
#include <stdio.h>

#include "lzw.h"

/* Function    : lzw_compress_file
   Description : Compresses the specified file.
   Expects     : source_file_name = The source file to compress.
                 dest_file_name   = The destination file.
   Returns     : The result of the operation (0 - no errors).
   Modified    : 09/28/90 DWP Initial coding.
   Notes       :
*/
int lzw_compress_file(char *source_file_name, char *dest_file_name) {
   FILE          *source_fp, *dest_fp;
   unsigned char *source_bufr, *dest_bufr;
   int           result;

   source_fp = fopen(source_file_name, "rb");
   dest_fp = fopen(dest_file_name, "wb");

   if (source_fp && dest_fp) {

      source_bufr = malloc(_lzw_buffer_size + sizeof(size_t));
      dest_bufr = malloc(_lzw_buffer_size + sizeof(size_t) + sizeof(unsigned char));

      if (source_bufr && dest_bufr) {

         while ((*((size_t *) source_bufr) = fread(source_bufr + sizeof(size_t), 1, _lzw_buffer_size, source_fp)) != 0) {

            if ((result = lzw_compress(source_bufr, dest_bufr)) == EZERO) {

               if (fwrite(dest_bufr, *((size_t *) dest_bufr) + sizeof(size_t) + sizeof(unsigned char), 1, dest_fp) == 0) {
                  result = errno;
                  break;
               }
            }
            else {
               break;
            }
         }
      }
      else {
         result = ENOMEM;
      }
      if (dest_bufr) {
         free(dest_bufr);
      }
      if (source_bufr) {
         free(source_bufr);
      }
   }
   else {
      result = ENOFILE;
   }
   if (dest_fp) {
      fclose(dest_fp);
   }
   if (source_fp) {
      fclose(source_fp);
   }

   return (result);
}
