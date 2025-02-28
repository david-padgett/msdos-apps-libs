/* File        : LZW2.C
   Module      : LZW
   System      : None
   Description : A method for decompressing blocks of data.
   Modified    : 09/28/90 DWP Created.
*/

#include <alloc.h>
#include <mem.h>

#include "lzw.h"
#include "Standard\standard.h"

/* Function    : lzw_expand
   Description : Expands a contiguous block of memory previously compressed
                 with lzw_compress.
   Expects     : source = The buffer for input data,
                             - buffer size (bytes 0 and 1),
                             - compression code (byte 2),
                             - the compressed data (bytes 3+).
                 dest   = The buffer for output data (undefined).
   Returns     : The result of the operation (0 - no errors).
   Modified    : 04/24/90 DWP Initial Coding.
   Notes       : 1) Uses PASCAL calling conventions.
                 2) 29,202 bytes must be available from DOS.
*/
pascal lzw_expand(unsigned char *source, unsigned char *dest) {
   size_t        i;
   lzw_code_data *code_array;
   unsigned char *src = source + sizeof(size_t) + sizeof(unsigned char), *dst = dest + sizeof(size_t), *string_array, ch;
   unsigned int  hash_var = (unsigned int) source[sizeof(size_t)], shift_var = 8 - source[sizeof(size_t)];
   unsigned int  max_code_value = (1 << (8 + source[sizeof(size_t)])) - 1;
   unsigned int  code, last_code  = 0, current_code = 256, temp_code, unaltered_code;
   int           exception_flag = FALSE, result = 0;

   /* Determine if the data was compressed with lzw_compress. */

   if (hash_var) {
      if ((code_array = malloc(CODE_ARRAY_SIZE)) != NULL) {
         if ((string_array = malloc(STRING_SIZE)) != NULL) {

            /* Read in the first code, output the first code. */

            *(dst++) = ch = (unsigned char) last_code = ((*src << 8) + *(src++ + 1)) >> shift_var;
            *((size_t *) dest) += 1;
            shift_var -= hash_var;

            /* Loop until there are no more codes to read. */

            while ((code = (unsigned int) ((((*src << 8) + *(src++ + 1)) >> shift_var) & max_code_value)) != max_code_value) {

               /* Update/adjust shifting variable. */

               if (!shift_var) {
                  src++;
                  shift_var = 8;
               }
               shift_var -= hash_var;

               /* Determine if the code is an actual compression code. */

               if (code > 255) {
                  unaltered_code = code;
                  i = STRING_SIZE;

                  /* If code is not in the translation table, use last
                     code plus the character (code). */

                  if (code >= current_code) {
                     string_array[i--] = ch;
                     exception_flag = TRUE;
                     temp_code = code;
                     code = last_code;
                  }

                  /* Expand the code. */

                  while (code > 255) {
                     string_array[i--] = code_array[code].ch;
                     code = code_array[code].string;

                     /* Check for stack overflow. */

                     if (!i) {
                        result = LZW_EXPAND_STACK_OVERFLOW_ERROR;
                        break;
                     }
                  }

                  /* Output the expanded string. */

                  *(dst++) = (unsigned char) code;
                  memcpy(dst, string_array + i + 1, STRING_SIZE - i);
                  dst += (STRING_SIZE - i);
                  *((size_t *) dest) += (STRING_SIZE - i) + 1;
               }
               else {

                  /* Not a true code, so just output it. */

                  *(dst++) = (unsigned char) code;
                  *((size_t *) dest) += 1;
                  unaltered_code = 0;
               }

               ch = (unsigned char) code;

               /* If there is room, add code to the translation table. */

               if (current_code < max_code_value) {
                  code_array[current_code].string = last_code;
                  code_array[current_code++].ch = ch;
               }

               if (exception_flag) {
                  exception_flag = FALSE;
                  code = temp_code;
               }

               if (unaltered_code) {
                  last_code = unaltered_code;
               }
               else {
                  last_code = code;
               }
            }
            free(string_array);
         }
         else {
            result = LZW_EXPAND_MEMORY_ALLOCATION_ERROR;
         }
         free(code_array);
      }
      else {
         result = LZW_EXPAND_MEMORY_ALLOCATION_ERROR;
      }
   }
   else {

      /* Data was not compressed, so copy it to the destination buffer. */

      memcpy(dst, src, *((size_t *) source));
      *((size_t *) dest) = *((unsigned int *) source);
   }
   return (result);
}
