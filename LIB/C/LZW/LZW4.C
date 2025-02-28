/* File        : LZW4.C
   Module      : LZW
   System      : None
   Description : A method for uncompressing files.
   Modified    : 09/28/90 DWP Created.
*/

#include <alloc.h>
#include <errno.h>
#include <mem.h>

#include "lzw.h"

/* Function    : lzw_uncompress_file
   Description : Un-compresses a file compressed with lzw_compress_file.
   Expects     : source_file_name = The name of the compressed file.
                 dest_file_name   = The name of the destination file.
   Returns     : The result of the operation (0 - no errors).
   Modified    : 09/28/90 DWP Initial coding.
   Notes       :
*/
int lzw_uncompress_file(char *source_file_name, char *dest_file_name) {
   FILE          *source_fp, *dest_fp;
   unsigned char *source_bufr, *dest_bufr;
   int           result;

   source_fp = fopen(source_file_name, "rb");
   dest_fp = fopen(dest_file_name, "wb");

   if (source_fp && dest_fp) {

      source_bufr = malloc(_lzw_buffer_size + sizeof(size_t) + sizeof(unsigned char));
      dest_bufr = malloc(_lzw_buffer_size + sizeof(size_t));

      if (source_bufr && dest_bufr) {

         /* Read in the header record. */

         while (fread(source_bufr, sizeof(size_t) + sizeof(unsigned char), 1, source_fp) != 0) {

            /* Read in the compressed data. */

            if (fread(source_bufr + sizeof(size_t) + sizeof(unsigned char), *((size_t *) source_bufr), 1, source_fp)) {

               setmem(dest_bufr, _lzw_buffer_size + sizeof(size_t), 0);

               if ((result = lzw_expand(source_bufr, dest_bufr)) == EZERO) {

                  /* Save the uncompressed data to the destination file. */

                  if (fwrite(dest_bufr + sizeof(size_t), *((size_t *) dest_bufr), 1, dest_fp) == 0) {
                     result = errno;
                     break;
                  }
               }
               else {
                  break;
               }
            }
            else {
               result = errno;
               break;
            }
         }
      }
      if (dest_bufr) {
         free(dest_bufr);
      }
      if (source_bufr) {
         free(source_bufr);
      }
   }
   if (dest_fp) {
      fclose(dest_fp);
   }
   if (source_fp) {
      fclose(source_fp);
   }

   return (result);
}