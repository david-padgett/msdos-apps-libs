/* File        : LZW1.C
   Module      : LZW
   System      : None
   Description : A method for compressing blocks of data.
   Modified    : 09/28/90 DWP Created.
*/

#include <alloc.h>
#include <errno.h>
#include <mem.h>

#include "lzw.h"
#include "Standard\standard.h"

/* Function    : lzw_compress
   Description : Compresses a contiguous block of memory using the Lempel-
                 Ziv-Welch data compression algorithm discussed in Dr. Dobbs
                 Journal, October, 1989, starting on page 29.  There are 3
                 different code lengths used in the compression, 9, 10, and
                 12 bits.  This algorithm tries each of the code lengths, the
                 code length with the best results is the one actually used.
   Expects     : source = The source buffer,
                             - source buffer size (bytes 0 and 1),
                             - the source data (bytes 2+).
                 dest   = The destination buffer, undefined upon entry,
                             - size of destination buffer (bytes 0 and 1),
                             - the compression code used (byte 2),
                             - the compressed data (bytes 3+).
   Returns     : The result of the operation (0 - no errors).
   Modified    : 04/20/90 DWP Initial Coding.
   Notes       : 1) Uses PASCAL calling conventions.
                 2) Requires that 25,106 bytes be available from DOS.
*/
pascal lzw_compress(unsigned char *source, unsigned char *dest) {
   size_t        best_size, dest_index, i;
   lzw_code_data *code_array;
   unsigned char *source_bufr_start, *dest_bufr_start = dest + sizeof(size_t) + sizeof(unsigned char), ch;
   unsigned int  hash_var, code_var, best_size_code = 0, string;
   unsigned int  current_code, max_code_value, terminate_level, final_pass_flag = FALSE;
   int           code, result = EZERO;

   if ((code_array = malloc(CODE_ARRAY_SIZE)) != NULL) {

      /* Determine what bit size to start with. */

      best_size = *((size_t *) source);
      hash_var = 4;
      if (best_size < 1023) {
         hash_var >>= 1;
         if (best_size < 511) {
            hash_var >>= 1;
         }
      }

      /* The start of the compression, including initializations. */

      lzw_compress_start:

      setmem(code_array, CODE_ARRAY_SIZE, 0);
      setmem(dest, *((size_t *) source), 0);
      source_bufr_start = source + sizeof(size_t);
      dest_index = 0;

      current_code = 256;
      code_var = 8 - hash_var;
      max_code_value = (1 << (hash_var + 8)) - 1;
      terminate_level = 0;

      /* Read in the first character. */

      string = *(source_bufr_start++);

      /* Loop until there are no more input characters. */

      for (i = 1; i < *((size_t *) source); i++) {

         /* Read in a character. */

         ch = *(source_bufr_start++);

         /* Determine if string plus the character is in the translation
            table. */

         code = ((ch << hash_var) ^ string);

         do {
            if (code_array[code].code) {

               /* Add the character to the string. */

               if ((code_array[code].string == string) && (code_array[code].ch == ch)) {
                  string = code_array[code].code;
                  break;
               }
               else {

                  /* No match, re-hash code and try again. */

                  code -= (code) ? TABLE_SIZE - code : 1;
                  if (code < 0) {
                     code += TABLE_SIZE;
                  }
               }
            }
            else {

               /* Code was not the in translation table, so add it if there
                  is room. */

               if (current_code + 1 < max_code_value) {
                  code_array[code].code = current_code++;
                  code_array[code].string = string;
                  code_array[code].ch = ch;
               }

               /* Output the code. */

               lzw_compress_output:

               /* If the size of the compressed buffer is larger than the
                  original data, stop compressing the data and exit. */

               if (dest_index + 1 < best_size) {
                  string <<= code_var;
                  dest_bufr_start[dest_index++] |= (string / 256);
                  dest_bufr_start[dest_index] |= (string % 256);
                  if (!code_var) {
                     dest_index++;
                     code_var = 8;
                  }
                  code_var -= hash_var;
                  string = ch;
               }
               else {
                  dest_index = i = *((size_t *) source);
               }
               break;
            }
         } while (TRUE);
      }

      switch (terminate_level++) {

                  /* Output the maximum code value (marks end of buffer). */

         case 1 : string = max_code_value;

                  /* Output remaining bits (flush the buffer). */

         case 0 :
         case 2 : goto lzw_compress_output;

                  /* Determine what to do next, try a smaller code or
                     exit. */

         case 3 : if (dest_index < best_size) {
                     best_size = dest_index;
                     best_size_code = hash_var;
                  }

                  /* Save size and compression code of destination buffer. */

                  *((size_t *) dest) = best_size;
                  dest[sizeof(size_t)] = best_size_code;

                  if (!final_pass_flag) {

                     /* Try a smaller code length if possible. */

                     if (hash_var > 1) {
                        hash_var >>= 1;
                        goto lzw_compress_start;
                     }

                     /* If best code length is 0, then compression is
                        inefficient. */

                     if (!best_size_code) {
                        *((size_t *) dest) = *((unsigned int *) source);
                        dest[sizeof(size_t)] = 0;
                        memcpy(dest + sizeof(size_t) + sizeof(unsigned char), source + sizeof(size_t), *((size_t *) source));
                     }
                     else {

                        /* Compression is more efficient, re-compress if best
                           code length is not the current code length. */

                        if (best_size_code != hash_var) {
                           hash_var = best_size_code;
                           final_pass_flag = TRUE;
                           goto lzw_compress_start;
                        }
                     }
                  }
      }
      free(code_array);
   }
   else {
      result = LZW_COMPRESS_MEMORY_ALLOCATION_ERROR;
   }
   return (result);
}
